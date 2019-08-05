//
// Created by pedrito on 03/08/19.
//


#include <SendablePacket.h>

class RequestTime : public SendablePacket {
	public:

		explicit RequestTime() : SendablePacket()
		{
			writeD(OP_REQUEST_TIME);
		}
};


