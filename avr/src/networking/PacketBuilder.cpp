//
// Created by ghisi on 03.09.22.
//

#include "PacketBuilder.h"

PacketBuilder::PacketBuilder() {
    state = State::START;
    nextIndex = 0;
}

PacketBuilder::~PacketBuilder() {
    delete[] packetData;
}

void PacketBuilder::add(uint8_t receivedByte) {
    switch (state) {
        case State::START:
            state = State::SIZE;
            break;
        case State::SIZE:
            size = receivedByte;
            state = State::DESTINATION;
            break;
        case State::DESTINATION:
            destination = receivedByte;
            state = State::SOURCE;
            break;
        case State::SOURCE:
            source = receivedByte;
            preparePacketData();
            state = State::REMAINING;
            break;
        case State::REMAINING:
            packetData[nextIndex] = receivedByte;
            break;
        case State::FINISHED:
            return;
    }
    nextIndex++;
    if (nextIndex == size) {
        state = State::FINISHED;
    }
}

Packet *PacketBuilder::build() {
    if (state == State::FINISHED) {
        auto* packet = new Packet(packetData);
        return packet;
    }
    return nullptr;
}

void PacketBuilder::preparePacketData() {
    packetData = new uint8_t[size];
    packetData[0] = Packet::PACKET_START;
    packetData[1] = size;
    packetData[2] = destination;
    packetData[3] = source;
}

bool PacketBuilder::isFinished() {
    return state == State::FINISHED;
}
