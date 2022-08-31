/*
 * NetworkInterface.cpp
 *
 *  Created on: Aug 30, 2022
 *      Author: ghisi
 */

#include "NetworkInterface.h"

NetworkInterface::~NetworkInterface() {

}

bool NetworkInterface::popFromReceiveQueue(Packet *packet) {
	return false;
}

bool NetworkInterface::pushToSendQueue(Packet*) {
	return false;
}

bool NetworkInterface::sendQueueIsEmpty() {
	return false;
}

bool NetworkInterface::receiveQueueIsEmpty() {
	return false;
}
