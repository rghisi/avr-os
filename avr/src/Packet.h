/*
 * Frame.h
 *
 *  Created on: Aug 27, 2022
 *      Author: ghisi
 */

#ifndef SRC_PACKET_H_
#define SRC_PACKET_H_
#include <stdint.h>
#include <stdio.h>

enum State {
	RESET, HEADER, PAYLOAD, FINISHED
};

class Packet {

public:
	Packet();
	void prepare(uint8_t destination, uint8_t source, uint8_t id,
			uint8_t totalFragments, uint8_t fragment, uint8_t payload[],
			uint8_t payloadSize);
	uint8_t next();
	bool hasNext();
	void reset();
	static const uint8_t HEADER_SIZE = 6;
	static const uint8_t MAX_PAYLOAD_SIZE = 255 - HEADER_SIZE;
private:
	void copyPayload(uint8_t data[], uint8_t size);
	uint8_t nextHeader();
	uint8_t nextPayload();
	uint8_t packetSize;
	uint8_t destination;
	uint8_t source;
	uint8_t id;
	uint8_t totalFragments;
	uint8_t fragment;
	uint8_t type;
	uint8_t payloadSize;
	uint8_t payload[MAX_PAYLOAD_SIZE];
	uint8_t index;
	State state;
};

#endif /* SRC_PACKET_H_ */
