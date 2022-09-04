/*
 * Frame_test.cpp
 *
 *  Created on: Aug 27, 2022
 *      Author: ghisi
 */

#include <gtest/gtest.h>
#include "../../avr/src/Packet.h"
#include "../../avr/src/CRC.h"

TEST(Packet, PrepareParingPacketMakesHasNextToBeTrue) {
	uint8_t destination = 0x0A;
	uint8_t source = 0x0B;
	uint8_t id = 0;
	uint8_t totalFragments = 1;
	uint8_t fragment = 0;
	uint8_t payload[] = "abcdefghijklmnopqrstuvxyz";
	uint8_t payloadSize = 25;
	auto* packet = new Packet(destination, source, id, totalFragments, fragment, payload, payloadSize);

	ASSERT_TRUE(packet->hasNext());
}

TEST(Packet, NextReturnsNextPacketByte) {
    uint8_t packetStart = 0b10100101;
	uint8_t destination = 0b01111111;
	uint8_t source = 0b01000010;
	uint8_t id = 0b10101010;
	uint8_t totalFragments = 0b01101011;
	uint8_t fragment = 0b01101011;
    uint8_t type = 0xFF;
	uint8_t payload[] = "a";
	uint8_t payloadSize = 2;
	uint8_t headerSize = 7;
    uint8_t crc_size = 1;
	uint8_t totalPacketSize = headerSize + payloadSize + crc_size;
    auto* packet = new Packet(destination, source, id, totalFragments, fragment, payload, payloadSize);

    ASSERT_TRUE(packet->hasNext());
    ASSERT_EQ(packetStart, packet->next());

	ASSERT_TRUE(packet->hasNext());
	ASSERT_EQ(totalPacketSize, packet->next());

	ASSERT_TRUE(packet->hasNext());
	ASSERT_EQ(destination, packet->next());

	ASSERT_TRUE(packet->hasNext());
	ASSERT_EQ(source, packet->next());

	ASSERT_TRUE(packet->hasNext());
	ASSERT_EQ(id, packet->next());

	ASSERT_TRUE(packet->hasNext());
    uint8_t expected = (totalFragments << 4) | (0x0F & fragment);
	ASSERT_EQ(expected, packet->next());

    ASSERT_TRUE(packet->hasNext());
    ASSERT_EQ(type, packet->next());

    ASSERT_TRUE(packet->hasNext());
    ASSERT_EQ('a', packet->next());
    ASSERT_TRUE(packet->hasNext());
    ASSERT_EQ(0x00, packet->next());

    ASSERT_TRUE(packet->hasNext());
    packet->next(); //crc - skip

    ASSERT_FALSE(packet->hasNext());
}

TEST(Packet, ShouldCalculateCorrectCRC_WhenCreated) {
    uint8_t destination = 0x01;
    uint8_t source = 0x02;
    uint8_t id = 0x01;
    uint8_t totalFragments = 0x01;
    uint8_t fragment = 0x00;
    uint8_t payload[] = "a";
    uint8_t payloadSize = 2;
    auto* packet = new Packet(destination, source, id, totalFragments, fragment, payload, payloadSize);

    uint8_t data[payloadSize + Packet::HEADER_SIZE + Packet::CRC_SIZE];

    uint8_t index = 0;

    uint8_t byte;
    while (packet->hasNext()) {
        byte = packet->next();
        data[index] = byte;
        index++;
    }
    uint8_t crc = byte;
    uint8_t rawCrc = CRC::calculate(data, payloadSize + Packet::HEADER_SIZE);

    ASSERT_EQ(rawCrc, crc);
}












