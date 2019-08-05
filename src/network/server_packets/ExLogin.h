//
// Created by pedrito on 03/08/19.
//

#include <ReceivablePacket.h>
#include "SendablePacket.h"

class ExLogin : public ReceivablePacket {
	public:

		/*
		 * Send server's date
		 */
		explicit ExLogin(ReceivablePacket *packet) : ReceivablePacket(packet)
		{
			int status = readD();
		}
};


