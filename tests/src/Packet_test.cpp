/*
 * Frame_test.cpp
 *
 *  Created on: Aug 27, 2022
 *      Author: ghisi
 */

#include <gtest/gtest.h>
#include "Packet.cpp"

TEST(Packet, PrepareParingPacketMakesHasNextToBeTrue) {
	Packet packet = Packet();
	uint8_t destination = 0x0A;
	uint8_t source = 0x0B;
	uint8_t id = 0;
	uint8_t totalFragments = 1;
	uint8_t fragment = 0;
	uint8_t payload[] = "abcdefghijklmnopqrstuvxyz";
	uint8_t payloadSize = 25;
	packet.prepare(destination, source, id, totalFragments, fragment, payload, payloadSize);

	ASSERT_TRUE(packet.hasNext());
}

TEST(Packet, NextReturnsNextPacketByte) {
	Packet packet = Packet();
	uint8_t destination = 0b01111111;
	uint8_t source = 0b01000010;
	uint8_t id = 0b10101010;
	uint8_t totalFragments = 0b01101011;
	uint8_t fragment = 0b01101011;
	uint8_t payload[] = "a";
	uint8_t payloadSize = 2;
	uint8_t headerSize = 6;
	uint8_t totalPacketSize = headerSize + payloadSize;
	packet.prepare(destination, source, id, totalFragments, fragment, payload, payloadSize);

	ASSERT_TRUE(packet.hasNext());
	ASSERT_EQ(totalPacketSize, packet.next());

	ASSERT_TRUE(packet.hasNext());
	uint8_t expectedDestinationPlusFirstBitOfSource = 0b11111111;
	ASSERT_EQ(expectedDestinationPlusFirstBitOfSource, packet.next());

	ASSERT_TRUE(packet.hasNext());
	uint8_t expectedSecondPartOfSourcePlusFirstTwoBitsOfId = 0b00001010;
	ASSERT_EQ(expectedSecondPartOfSourcePlusFirstTwoBitsOfId, packet.next());

	ASSERT_TRUE(packet.hasNext());
	uint8_t expectedLastSixBitsOfIdPlusFirstTwoBitsOfTotalFragments = 0b10101011;
	ASSERT_EQ(expectedLastSixBitsOfIdPlusFirstTwoBitsOfTotalFragments, packet.next());

	ASSERT_TRUE(packet.hasNext());
	uint8_t expectedLastFiveBitsOfTotalFragmentsPlusFirstThreBitsOfFragment = 0b01011110;
	ASSERT_EQ(expectedLastFiveBitsOfTotalFragmentsPlusFirstThreBitsOfFragment, packet.next());
}













