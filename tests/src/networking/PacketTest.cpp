/*
 * Frame_test.cpp
 *
 *  Created on: Aug 27, 2022
 *      Author: ghisi
 */

#include <gtest/gtest.h>
#include "../../../avr/src/networking/Packet.h"
#include "../../../avr/src/std/CRC.h"

TEST(Packet, PrepareParingPacketMakesHasNextToBeTrue) {
	uint8_t destination = 0x0A;
	uint8_t source = 0x0B;
	uint16_t id = 0;
    uint8_t service = 0x01;
	uint8_t payload[] = "abcdefghijklmnopqrstuvxyz";
	uint8_t payloadSize = 25;
	auto* packet = new Packet(destination, source, id, service, payload, payloadSize);

	ASSERT_TRUE(packet->isValid());
}

TEST(Packet, NextReturnsNextPacketByte) {
    uint8_t packetStart = 0b10100101;
	uint8_t destination = 0b01111111;
	uint8_t source = 0b01000010;
	uint16_t id = 0b10101010;
    uint8_t service = 0x01;
	uint8_t payload[] = "a";
	uint8_t payloadSize = 2;
	uint8_t headerSize = 7;
    uint8_t crc_size = 1;
	uint8_t totalPacketSize = headerSize + payloadSize + crc_size;
    auto* packet = new Packet(destination, source, id, service, payload, payloadSize);

//    ASSERT_TRUE(packet->hasNext());
//    ASSERT_EQ(packetStart, packet->next());
//
//	ASSERT_TRUE(packet->hasNext());
//	ASSERT_EQ(totalPacketSize, packet->next());
//
//	ASSERT_TRUE(packet->hasNext());
//	ASSERT_EQ(destination, packet->next());
//
//	ASSERT_TRUE(packet->hasNext());
//	ASSERT_EQ(source, packet->next());
//
//	ASSERT_TRUE(packet->hasNext());
//	ASSERT_EQ(id, packet->next());
//
//	ASSERT_TRUE(packet->hasNext());
//    uint8_t expected = (totalFragments << 4) | (0x0F & fragment);
//	ASSERT_EQ(expected, packet->next());
//
//    ASSERT_TRUE(packet->hasNext());
//    ASSERT_EQ(type, packet->next());
//
//    ASSERT_TRUE(packet->hasNext());
//    ASSERT_EQ('a', packet->next());
//    ASSERT_TRUE(packet->hasNext());
//    ASSERT_EQ(0x00, packet->next());
//
//    ASSERT_TRUE(packet->hasNext());
//    packet->next(); //crc - skip
//
//    ASSERT_FALSE(packet->hasNext());
}

TEST(Packet, ShouldCalculateCorrectCRC_WhenCreated) {
    uint8_t destination = 0x01;
    uint8_t source = 0x02;
    uint16_t id = 0xF00F;
    uint8_t service = 0x01;
    uint8_t payload[] = { 'a' };
    uint8_t payloadSize = 1;
    uint8_t packetSize = payloadSize + Packet::HEADER_SIZE;
    auto* packet = new Packet(destination, source, id, service, payload, payloadSize);

    auto *rawPacket = new uint8_t[] {
        Packet::PACKET_START_SYMBOL,
        destination,
        source,
        packetSize,
        (uint8_t) (id >> 8),
        (uint8_t) id,
        service,
        'a'
    };

    uint8_t expectedCrc = CRC::calculate(rawPacket, packetSize - 1);

    ASSERT_EQ(expectedCrc, packet->crc());
    ASSERT_TRUE(packet->isValid());
}












