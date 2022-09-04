/*
 * PacketFragmenter.h
 *
 *  Created on: Aug 28, 2022
 *      Author: ghisi
 */

#ifndef SRC_PACKETFACTORY_H_
#define SRC_PACKETFACTORY_H_
#include <stdint.h>
#include <stdio.h>
#include "Packet.h"

class PacketFactory {
public:
	PacketFactory();
	void prepare(uint8_t destination, uint8_t source, uint8_t payload[],
		uint16_t payloadSize);
	Packet nextPacket();
	bool hasNextPacket();
private:
	void copyPayload(uint16_t copyLimit);
	uint8_t id;
	uint8_t totalFragments;
	uint8_t fragment;
	uint8_t destination;
	uint8_t source;
	uint8_t* payload;
	uint16_t payloadSize;
	uint16_t payloadOffset;
	Packet packet;
	uint8_t payloadFragment[Packet::MAX_PAYLOAD_SIZE];
	uint16_t payloadFragmentSize;
};

#endif /* SRC_PACKETFACTORY_H_ */
