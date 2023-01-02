/*
 * SerialInterface.h
 *
 *  Created on: Aug 30, 2022
 *      Author: ghisi
 */

#ifndef NETWORKINTERFACE_H_
#define NETWORKINTERFACE_H_
#include "Packet.h"
#include "../system/Subscriber.h"

class NetworkInterface: public EventHandler {
public:
    virtual ~NetworkInterface() = default;
    virtual uint8_t getAddress() = 0;
};

#endif /* NETWORKINTERFACE_H_ */
