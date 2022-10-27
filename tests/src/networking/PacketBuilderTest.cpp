//
// Created by ghisi on 03.09.22.
//

#include <gtest/gtest.h>
#include "../../../avr/src/networking/Packet.h"
#include "../../../avr/src/networking/PacketBuilder.h"

TEST(PacketBuilder, PrepareParingPacketMakesHasNextToBeTrue) {
    uint8_t destination = 0x0A;
    uint8_t source = 0x0B;
    uint8_t idMsb = 0x01;
    uint8_t idLsb = 0x02;
    uint8_t service = 0x05;
    uint8_t crc = 0x0A;
    uint8_t packetLength = Packet::HEADER_SIZE + 3;
    auto* packetBytes = new uint8_t[] {
            Packet::PACKET_START_SYMBOL,
            destination,
            source,
            packetLength,
            idMsb,
            idLsb,
            service,
            crc,
            'a',
            'b',
            'c',
    };

    auto builder = PacketBuilder();

    for (int i = 0; i < packetLength; ++i) {
        builder.add(packetBytes[i]);
    }

    ASSERT_TRUE(builder.isFinished());

    Packet* receivedPacket = builder.build();

    ASSERT_EQ(destination, receivedPacket->destination());
    ASSERT_EQ(source, receivedPacket->source());
    ASSERT_EQ(packetLength, receivedPacket->length());
    ASSERT_EQ(crc, receivedPacket->crc());
    ASSERT_EQ(3, receivedPacket->payloadLength());
}