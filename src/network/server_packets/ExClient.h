//
// Created by pedrito on 03/08/19.
//

#include <ReceivablePacket.h>

class ExClient : public ReceivablePacket {
	public:

		/*
		 * Send server's date
		 */
		explicit ExClient(ReceivablePacket *packet) : ReceivablePacket(packet)
		{
			long id = readQ();
			std::cout << "New client " << id << std::endl;
			getClient()->addPlayer(id, new Player);
		}
};


