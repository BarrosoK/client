//
// Created by pedrito on 03/08/19.
//


#include <SendablePacket.h>

class RequestLogin : public SendablePacket {
	public:

		explicit RequestLogin(std::string pseudo) : SendablePacket()
		{
			writeD(OP_REQUEST_LOGIN);
			writeS(pseudo);
		}
};


