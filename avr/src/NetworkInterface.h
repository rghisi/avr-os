/*
 * SerialInterface.h
 *
 *  Created on: Aug 30, 2022
 *      Author: ghisi
 */

#ifndef NETWORKINTERFACE_H_
#define NETWORKINTERFACE_H_
#include "Packet.h"

class NetworkInterface {
public:
	virtual ~NetworkInterface();
	virtual bool pushToSendQueue(Packet* packet);
	virtual bool sendQueueIsEmpty();
	virtual bool receiveQueueIsEmpty();
	virtual bool popFromReceiveQueue(Packet* packet);

};

#endif /* NETWORKINTERFACE_H_ */
