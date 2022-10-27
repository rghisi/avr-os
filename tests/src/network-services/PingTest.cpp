//
// Created by ghisi on 14.09.22.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include "../../../avr/src/network-services/Ping.h"

class MockSender : public PacketSender {
public:
    Packet *packet = nullptr;
    uint8_t address = 0;

    MockSender(uint8_t address) {
        this->address = address;
    }

    bool send(Packet *datagram) override {
        this->packet = datagram;
        return true;
    }
    uint8_t sourceAddress() override {
        return address;
    }
};

TEST(Ping, ShouldSendPingMessage_WhenPingIsCalled) {
    MockSender sender = MockSender(0xAB);

    auto ping = Ping(&sender);
    ping.ping(0xCD);

    ASSERT_EQ(0xAB, sender.packet->source());
    ASSERT_EQ(0xCD, sender.packet->destination());
    ASSERT_EQ(0x01, sender.packet->service());
    ASSERT_EQ(0x04, sender.packet->payloadLength());
//    ASSERT_EQ('P', sender.datagram->pa);
//    ASSERT_EQ('I', sender.datagram->data[1]);
//    ASSERT_EQ('N', sender.datagram->data[2]);
//    ASSERT_EQ('G', sender.datagram->data[3]);
}

TEST(Ping, ShouldReplyPongMessage_WhenPingIsReceived) {
    auto *sender = new MockSender(0xCD);
    auto ping = Ping(sender);
    uint8_t pingData[] = {'P', 'I', 'N', 'G'};
    auto *packet = new Packet(0xCD, 0xAB, 0x00, ping.service(), pingData, 0x04);

    ping.receive(packet);

    ASSERT_EQ(0xCD, sender->packet->source());
    ASSERT_EQ(0xAB, sender->packet->destination());
    ASSERT_EQ(0x01, sender->packet->service());
    ASSERT_EQ(0x04, sender->packet->payloadLength());
//    ASSERT_EQ('P', sender->datagram->data[0]);
//    ASSERT_EQ('O', sender->datagram->data[1]);
//    ASSERT_EQ('N', sender->datagram->data[2]);
//    ASSERT_EQ('G', sender->datagram->data[3]);
}

TEST(Ping, ShouldNotReply_WhenPingIsNotReceived) {
    auto *sender = new MockSender(0xCD);
    auto ping = Ping(sender);
    uint8_t pingData[] = {'A', 'B', 'C', 'D'};
    auto *packet = new Packet(0xCD, 0xAB, 0x01, ping.service(), pingData, 0x04);

    ping.receive(packet);

    ASSERT_EQ(nullptr, sender->packet);
}