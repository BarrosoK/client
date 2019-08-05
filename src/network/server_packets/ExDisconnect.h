//
// Created by pedrito on 03/08/19.
//

#include <ReceivablePacket.h>

class ExDisconnect : public ReceivablePacket {
	public:

		/*
		 * Send server's date
		 */
		explicit ExDisconnect(ReceivablePacket *packet) : ReceivablePacket(packet)
		{
			long id = readQ();
			std::cout << "Client disconnected " << id << std::endl;
			// getClient()->addPlayer(id, new Player);
		}
};


