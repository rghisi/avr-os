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
    virtual ~NetworkInterface() = default;
    virtual bool pushToSendQueue(Packet* packet) = 0;
    virtual Packet* popFromReceiveQueue() = 0;
    virtual bool acceptsPacket() = 0;
    virtual bool receiveQueueHasPackets() = 0;
    virtual uint8_t nextByteToSend() = 0;
};

#endif /* NETWORKINTERFACE_H_ */
