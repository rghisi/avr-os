//
// Created by ghisi on 09.10.22.
//

#include <gtest/gtest.h>
#include "../../../avr/src/networking/Packet.h"
#include "../../../avr/src/networking/PacketReader.h"

TEST(PacketReader, ShouldReturnFalse_WhenHasNextFrameIsIssuedAgainstNoPacket) {
    auto packetReader = PacketReader();

    ASSERT_FALSE(packetReader.hasNextFrame());
    ASSERT_EQ(0, packetReader.nextFrame());
}

TEST(PacketReader, ShouldReturnFalse_WhenLastFrameOfThePacketIsReached) {
    uint8_t destination = 0x0A;
    uint8_t source = 0x0B;
    uint16_t id = 0x01;
    uint8_t service = 0x05;
    auto *data = new uint8_t[] {'d', 'a', 't', 'a'};
    uint8_t dataLength = 4;
    auto *packet = new Packet(destination, source, id, service, data, dataLength);
    auto packetReader = PacketReader();

    packetReader.read(packet);

    ASSERT_TRUE(packetReader.hasNextFrame());
    packetReader.nextFrame();
    packetReader.nextFrame();
    packetReader.nextFrame();
    packetReader.nextFrame();
    packetReader.nextFrame();
    packetReader.nextFrame();
    packetReader.nextFrame();
    packetReader.nextFrame();
    packetReader.nextFrame();
    packetReader.nextFrame();
    packetReader.nextFrame();
    packetReader.nextFrame();
    ASSERT_FALSE(packetReader.hasNextFrame());
    ASSERT_EQ(0, packetReader.nextFrame());
}