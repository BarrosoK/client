//
// Created by pedrito on 03/08/19.
//

#ifndef SERVER_RECEIVABLEPACKET_H
#define SERVER_RECEIVABLEPACKET_H

#include <iostream>
#include <cstring>

class Client;

enum RECEIVABLE_OPCODE: int {
	OP_EX_LOGIN = 2,
	OP_EX_KICK = 4,
	OP_EX_OTHER = 5,
	OP_EX_NEW_CLIENT = 6,
	OP_EX_DISCONNECT = 7,
	OP_EX_CONNECTION = 15,
	OP_EX_SAY = 23,
	OP_EX_DATE = 25,
	OP_EX_TIME = 26,
};

class ReceivablePacket {
	private:
		unsigned char *buffer;
		unsigned int pos = 0;
		int opCode;
		Client *client;
	protected:
		ReceivablePacket(ReceivablePacket *pPacket);
	public:
		ReceivablePacket(unsigned char *buff, Client *client);
		virtual ~ReceivablePacket();
		int getOpCode();
		Client *getClient();
		unsigned char *getData();
		int readD();
		int readC();
		std::string readS();
		long readQ();
		short readH();
};

#endif //SERVER_RECEIVABLEPACKET_H
