/*
 * Author: pedrito.
 * Date: 05/08/19
 */

#ifndef CONSOLE_CLIENT_H
#define CONSOLE_CLIENT_H

#include <iostream>
#include <netdb.h>
#include <strings.h>
#include <zconf.h>
#include "SendablePacket.h"
#include "ReceivablePacket.h"
#include <thread>
#include <vector>
#include "Player.h"


#define BUFFER_SIZE 512

class Client {
	private:
		int socketFd, port;
		struct sockaddr_in svrAdd;
		struct hostent *server;
		long id = 0;
		std::thread *listener;
		bool connected = false;
		unsigned char buffer[BUFFER_SIZE];
		std::vector<std::pair<long, Player *>> players;
	public:
		Client(std::string address, int port);
		~Client();
		void listen();
		void mainLoop();
		void parseInput();
		void waitForId();
		void waitForOther();
		ssize_t sendPacket(SendablePacket *packet);
		void addPlayer(long id, Player *p);
};

#endif //CONSOLE_CLIENT_H
