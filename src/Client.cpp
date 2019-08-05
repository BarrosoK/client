/*
 * Author: pedrito.
 * Date: 05/08/19
 */



#include <Client.h>
#include <client_packets/RequestLogin.h>
#include <client_packets/RequestOther.h>
#include <server_packets/ExClient.h>
#include <server_packets/ExDisconnect.h>
#include <client_packets/RequestTime.h>
#include <client_packets/RequestDate.h>

#include "Client.h"

Client::Client(std::string address, int port)
:port(port)
{
	if ((port > 65535) || (port < 2000)) {
		std::cerr << "Please enter port number between 2000 - 65535" << std::endl;
		return;
	}

	socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//create client skt

	if (socketFd < 0) {
		std::cerr << "Cannot open socket" << std::endl;
		return;
	}

	server = gethostbyname(address.c_str());

	if (server == NULL) {
		std::cerr << "Host does not exist" << std::endl;
		return;
	}

	bzero((char *)&svrAdd, sizeof(svrAdd));
	svrAdd.sin_family = AF_INET;

	bcopy((char *)server->h_addr, (char *)&svrAdd.sin_addr.s_addr, server->h_length);

	svrAdd.sin_port = htons(port);

	int checker = connect(socketFd, (struct sockaddr *)&svrAdd, sizeof(svrAdd));

	if (checker < 0) {
		std::cerr << "Cannot connect!" << std::endl;
		return;
	}
	waitForId();
	waitForOther();
	mainLoop();
}

Client::~Client()
{
}

void Client::waitForId()
{
	while (!id) {
		// Wait for an id
		bzero(buffer, 300);
		ssize_t n = (recv(socketFd, buffer, sizeof buffer, 0));
		ReceivablePacket p(buffer, NULL);
		if (p.getOpCode() == OP_EX_CONNECTION) {
			id = p.readQ();
			connected = true;
			std::cout << "Received id " << id << " from server" << std::endl;
		}
	}
}

void Client::listen()
{
	unsigned char buffer[512];
	ssize_t n;

	while (true) {
		bzero(buffer, BUFFER_SIZE);

		n = (recv(socketFd, buffer, sizeof buffer, 0));
		if (n <= 0) {
			std::cout << "Server error" << std::endl;
			break;
		}
		ReceivablePacket packet(buffer, this);
		int opcode = packet.getOpCode();
		std::cout << "Received packet (" << n << ")  with opcode: " << opcode << std::endl;
		switch (opcode) {
			case OP_EX_NEW_CLIENT : {
				new ExClient(&packet);
				break;
			}
			case OP_EX_DISCONNECT: {
				new ExDisconnect(&packet);
				break;
			}
			case OP_EX_KICK: {
				std::string reason = packet.readS();
				std::cout << "You got kicked, reason: " << reason << std::endl;
				break;
			}
			case OP_EX_SAY: {
				std::string msg = packet.readS();
				std::cout << "Server sent you a msg: " << msg << std::endl;
				break;
			}
			case OP_EX_TIME: {
				std::string time = packet.readS();
				std::cout << "Server's time: " << time << std::endl;
				break;
			}
			case OP_EX_DATE: {
				std::string date = packet.readS();
				std::cout << "Server's date: " << date << std::endl;
				break;
			}
			default: {
				break;
			}
		}
	}
}

void Client::mainLoop()
{
	listener = new std::thread(&Client::listen, this);
	while (connected) {
		bzero(buffer, BUFFER_SIZE);
		parseInput();
	}
	if (listener->joinable()) {
		listener->join();
	}
	close(socketFd);
	std::cout << "Bye" << std::endl;
}

void Client::parseInput()
{
	int opcode = 0;

	std::cout << "OPCODE: ";
	std::cin >> opcode;
	switch (opcode) {
		case OP_REQUEST_LOGIN: {
			std::string pseudo;
			std::cout << "pseudo: ";
			std::cin >> pseudo;
			sendPacket(new RequestLogin(pseudo));
		}
		case OP_REQUEST_TIME: {
			sendPacket(new RequestTime());
			break;
		}
		case OP_REQUEST_DATE: {
			sendPacket(new RequestDate());
			break;
		}
	}

}

ssize_t Client::sendPacket(SendablePacket *packet)
{
	ssize_t n = write(socketFd, packet->getBuffer(), packet->getSize());
	if (n <= 0) {
		std::cout << "Error sending packet" << std::endl;
		connected = false;
	}
	return n;
}

void Client::waitForOther()
{
	bool waiting = true;
	sendPacket(new RequestOther());
	while (waiting) {
		// Wait for an id
		bzero(buffer, 300);
		ssize_t n = (recv(socketFd, buffer, sizeof buffer, 0));
		if (n <= 0) {
			std::cerr << "error" << std::endl;
		}
		ReceivablePacket p(buffer, NULL);
		if (p.getOpCode() == OP_EX_OTHER) {
			long total = p.readQ();
			for (long i = 0; i < total; i++) {
				players.push_back(std::make_pair(p.readQ(), new Player()));
			}
			std::cout << "Received a total of " << total << " players" << std::endl;
			waiting = false;
		}
	}
}

void Client::addPlayer(long id, Player *p)
{
	players.push_back(std::make_pair(id, p));
}
