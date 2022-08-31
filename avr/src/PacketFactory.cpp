/*
 * PacketFragmenter.cpp
 *
 *  Created on: Aug 28, 2022
 *      Author: ghisi
 */

#include "PacketFactory.h"

PacketFactory::PacketFactory() {
	this->destination = 0;
	this->source = 0;
	this->payloadFragmentSize = 0;
	this->payloadOffset = 0;
	this->payloadSize = 0;
	this->payload = 0;
	this->id = 0;
	this->totalFragments = 0;
	this->fragment = 0xFF;
}

void PacketFactory::prepare(uint8_t destination, uint8_t source, uint8_t payload[],
		uint16_t payloadSize) {
	this->totalFragments = (uint8_t)(payloadSize / (uint16_t)Packet::MAX_PAYLOAD_SIZE);
	if ((payloadSize % (uint16_t)Packet::MAX_PAYLOAD_SIZE) > 0) {
		totalFragments++;
	}

	this->fragment = 0;
	this->destination = destination;
	this->source = source;
	this->payload = payload;
	this->payloadSize = payloadSize;
	this->payloadOffset = 0;
	this->id++;
}

Packet PacketFactory::nextPacket() {
	payloadFragmentSize = payloadSize - payloadOffset;
	if (payloadFragmentSize > Packet::MAX_PAYLOAD_SIZE) {
		payloadFragmentSize = Packet::MAX_PAYLOAD_SIZE;
	}
	copyPayload(payloadFragmentSize);
	packet.prepare(destination, source, id, totalFragments, fragment, payloadFragment, payloadFragmentSize);

	payloadOffset += payloadFragmentSize;
	fragment++;

	return packet;
}

bool PacketFactory::hasNextPacket() {
	return fragment < totalFragments;
}

void PacketFactory::copyPayload(uint16_t size) {
	uint16_t limit = payloadOffset + size;
	uint8_t payloadFragmentIndex = 0;
	for (uint16_t i = payloadOffset; i < limit; i++) {
		this->payloadFragment[payloadFragmentIndex] = payload[i];
		payloadFragmentIndex++;
	}
}

