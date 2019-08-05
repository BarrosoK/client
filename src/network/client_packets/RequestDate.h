//
// Created by pedrito on 03/08/19.
//


#include <SendablePacket.h>

class RequestDate : public SendablePacket {
	public:

		explicit RequestDate() : SendablePacket()
		{
			writeD(OP_REQUEST_DATE);
		}
};


