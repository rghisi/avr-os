/*
 * Frame.cpp
 *
 *  Created on: Aug 27, 2022
 *      Author: ghisi
 */

#include "Packet.h"

Packet::Packet() {
	this->state = RESET;
}

void Packet::prepare(uint8_t destination, uint8_t source, uint8_t id,
		uint8_t totalFragments, uint8_t fragment, uint8_t payload[],
		uint8_t payloadSize) {
	this->destination = destination;
	this->source = source;
	this->packetSize = payloadSize + HEADER_SIZE;
	this->payloadSize = payloadSize;
	this->id = id;
	this->totalFragments = totalFragments;
	this->fragment = fragment;
	this->type = 0xFF;
	copyPayload(payload, payloadSize);
	this->reset();
}

void Packet::copyPayload(uint8_t inputData[], uint8_t inputDataSize) {
	for (uint8_t i = 0; i < inputDataSize; i++) {
		this->payload[i] = inputData[i];
	}
}

void Packet::reset() {
	state = HEADER;
	index = 0;
}

bool Packet::hasNext() {
	return state != RESET && state != FINISHED;
}

uint8_t Packet::next() {
	switch (state) {
	case HEADER:
		return nextHeader();
	case PAYLOAD:
		return nextPayload();
	default:
		return 0;
	}
}

uint8_t Packet::nextHeader() {
	uint8_t output = 0;
	switch (index) {
	case 0:
		output = packetSize;
		break;
	case 1:
		output = (destination << 1) | ((0b01000000 & source) >> 6);
		break;
	case 2:
		output = (source << 2) | ((0b11000000 & id) >> 6);
		break;
	case 3:
		output = (id << 2) | ((0b01100000 & totalFragments) >> 5);
		break;
	case 4:
		output = (totalFragments << 3) | ((0b01110000 & fragment) >> 4);
		break;
	case 5:
		output = (fragment << 4) | ((0b00001111 & type));
		break;
	}
	index++;
	if (index == HEADER_SIZE) {
		state = PAYLOAD;
		index = 0;
	}

	return output;
}

uint8_t Packet::nextPayload() {
	uint8_t output = payload[index];
	index++;
	if (index == payloadSize) {
		state = FINISHED;
	}

	return output;
}
