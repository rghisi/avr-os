//
// Created by ghisi on 03.09.22.
//

#include "PacketBuilder.h"
#include "../collections/Array.h"

PacketBuilder::PacketBuilder() {
    state = State::WAITING_PACKET_START;
    payloadIndex = 0;
    payloadLength = 0;
    crc = 0;
}

void PacketBuilder::add(uint8_t receivedByte) {
    switch (state) {
        case State::WAITING_PACKET_START:
            if (receivedByte == Packet::PACKET_START_SYMBOL) {
                state = State::DESTINATION;
            }
            break;
        case State::DESTINATION:
            destination = receivedByte;
            state = State::SOURCE;
            break;
        case State::SOURCE:
            source = receivedByte;
            state = State::LENGTH;
            break;
        case State::LENGTH:
            payloadLength = receivedByte - Packet::HEADER_SIZE;
            packetPayload = std::make_unique<uint8_t[]>(payloadLength);
            state = State::ID_MSB;
            break;
        case State::ID_MSB:
            id = ((uint16_t)receivedByte) << 8;
            state = State::ID_LSB;
            break;
        case State::ID_LSB:
            id |= receivedByte;
            state = State::SERVICE;
            break;
        case State::SERVICE:
            service = receivedByte;
            state = State::CRC;
            break;
        case State::CRC:
            crc = receivedByte;
            state = State::PAYLOAD;
            break;
        case State::PAYLOAD:
            packetPayload[payloadIndex++] = receivedByte;
            if (payloadIndex == payloadLength) {
                state = State::FINISHED;
            }
            break;
        case State::FINISHED:
            return;
    }
}

std::unique_ptr<Packet> PacketBuilder::build() {
    if (state == State::FINISHED) {
        auto packet = std::make_unique<Packet>(Packet(destination, source, id, service, crc, std::move(packetPayload), payloadLength));
        reset();
        return std::move(packet);
    }

    return nullptr;
}

void PacketBuilder::reset() {
    state = State::WAITING_PACKET_START;
    payloadIndex = 0;
    payloadLength = 0;
    this->packetPayload = nullptr;
}

bool PacketBuilder::isFinished() {
    return state == State::FINISHED;
}
