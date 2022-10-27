//
// Created by ghisi on 07.10.22.
//

#ifndef AVR_PACKETREADER_H
#define AVR_PACKETREADER_H

#include "cstdint"
#include "Packet.h"

class PacketReader {
public:
    PacketReader();
    void read(Packet *packet);
    bool hasNextFrame();
    uint8_t nextFrame();
    Packet *packet();

private:
    Packet *packetBeingRead;
    uint8_t currentFrame;
    uint8_t numberOfFrames;
    bool hasNext;
};


#endif //AVR_PACKETREADER_H
