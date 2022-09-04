//
// Created by ghisi on 03.09.22.
//

#include <gtest/gtest.h>
#include "../../avr/src/Packet.h"
#include "../../avr/src/PacketBuilder.h"

TEST(PacketBuilder, PrepareParingPacketMakesHasNextToBeTrue) {
    uint8_t destination = 0x0A;
    uint8_t source = 0x0B;
    uint8_t id = 0;
    uint8_t totalFragments = 1;
    uint8_t fragment = 0;
    uint8_t payload[] = "abcdefghijklmnopqrstuvxyz";
    uint8_t payloadSize = 26;
    auto* sendPacket = new Packet(destination, source, id, totalFragments, fragment, payload, payloadSize);

    auto* builder = new PacketBuilder();

    while (sendPacket->hasNext()) {
        builder->add(sendPacket->next());
    }

    Packet* receivedPacket = builder->build();

    sendPacket->reset();
    while (sendPacket->hasNext()) {
        ASSERT_EQ(sendPacket->next(), receivedPacket->next());
    }

    ASSERT_FALSE(receivedPacket->hasNext());
}