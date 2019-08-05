//
// Created by pedrito on 03/08/19.
//


#include <SendablePacket.h>

class RequestOther : public SendablePacket {
	public:

		explicit RequestOther() : SendablePacket()
		{
			writeD(OP_REQUEST_OTHER);
		}
};


