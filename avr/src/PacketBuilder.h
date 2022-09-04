//
// Created by ghisi on 03.09.22.
//

#ifndef AVR_PACKETBUILDER_H
#define AVR_PACKETBUILDER_H

#include <stdint.h>
#include "Packet.h"

class PacketBuilder {
public:
    PacketBuilder();
    ~PacketBuilder();
    void add(uint8_t receivedByte);
    Packet *build();
    bool isFinished();
private:
    void preparePacketData();
    enum class State {
        START, SIZE, DESTINATION, SOURCE, REMAINING, FINISHED
    };
    State state;
    uint8_t size;
    uint8_t destination;
    uint8_t source;
    uint8_t nextIndex;
    uint8_t* packetData;
};


#endif //AVR_PACKETBUILDER_H
