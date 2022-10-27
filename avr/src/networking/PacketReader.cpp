//
// Created by ghisi on 07.10.22.
//

#include "PacketReader.h"

PacketReader::PacketReader() {
    numberOfFrames = 0;
    currentFrame = 0;
    hasNext = false;
    packetBeingRead = nullptr;
}

Packet *PacketReader::packet() {
    return packetBeingRead;
}

void PacketReader::read(Packet *packet) {
    this->packetBeingRead = packet;
    numberOfFrames = packet->length();
    currentFrame = 0;
    hasNext = currentFrame < numberOfFrames;
}

bool PacketReader::hasNextFrame() {
    return hasNext;
}

uint8_t PacketReader::nextFrame() {
    uint8_t frame = 0;
    if (hasNext) {
        switch (currentFrame) {
            case Packet::START_INDEX:
                frame = Packet::PACKET_START_SYMBOL;
                break;
            case Packet::DESTINATION_INDEX:
                frame = packetBeingRead->destination();
                break;
            case Packet::SOURCE_INDEX:
                frame = packetBeingRead->source();
                break;
            case Packet::LENGTH_INDEX:
                frame = packetBeingRead->length();
                break;
            case Packet::ID_MSB_INDEX:
                frame = packetBeingRead->id() >> 8;
                break;
            case Packet::ID_LSB_INDEX:
                frame = packetBeingRead->id();
                break;
            case Packet::SERVICE_INDEX:
                frame = packetBeingRead->service();
                break;
            case Packet::CRC_INDEX:
                frame = packetBeingRead->crc();
                break;
            default:
                frame = packetBeingRead->payload()[currentFrame - Packet::HEADER_SIZE];
                break;
        }
        currentFrame++;
        if (currentFrame >= numberOfFrames) {
            hasNext = false;
        }
    }
    return frame;
}
