//
// Created by ghisi on 03.09.22.
//

#ifndef AVR_PACKETBUILDER_H
#define AVR_PACKETBUILDER_H

#include <cstdint>
#include "Packet.h"
#include "memory"

class PacketBuilder {
public:
    PacketBuilder();
    void add(uint8_t receivedByte);
    std::unique_ptr<Packet> build();
    bool isFinished();

private:
    void reset();
    enum class State {
        WAITING_PACKET_START, DESTINATION, SOURCE, LENGTH, ID_MSB, ID_LSB, SERVICE, CRC, PAYLOAD, FINISHED
    };
    State state;
    uint8_t destination;
    uint8_t source;
    uint8_t payloadLength;
    uint16_t id;
    uint8_t service;
    uint8_t crc;
    uint8_t payloadIndex;
    std::unique_ptr<uint8_t[]> packetPayload;
};


#endif //AVR_PACKETBUILDER_H
