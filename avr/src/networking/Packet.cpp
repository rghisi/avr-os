/*
 * Frame.cpp
 *
 *  Created on: Aug 27, 2022
 *      Author: ghisi
 */

#include "Packet.h"
#include "../std/CRC.h"

Packet::Packet(uint8_t destination, uint8_t source, uint8_t id,
               uint8_t totalFragments, uint8_t fragment, uint8_t *payload,
               uint8_t payloadSize) {
    this->destination = destination;
    this->source = source;
    this->payloadSize = payloadSize;
    this->packetSize = payloadSize + HEADER_SIZE + CRC_SIZE;
    this->packetData = new uint8_t[packetSize];
    packetData[0] = PACKET_START;
    packetData[1] = packetSize;
    packetData[2] = destination;
    packetData[3] = source;
    packetData[4] = id;
    packetData[5] = (totalFragments << 4) | (0b00001111 & fragment);
    packetData[6] = 0xFF;
    copyPayload(payload, payloadSize);
    addCrc();
    this->index = 0;
}

Packet::Packet(uint8_t *packetData) {
    this->packetSize = packetData[1];
    this->packetData = new uint8_t[packetSize];
    copyPacketData(packetData, this->packetSize);
    this->index = 0;
}

Packet::~Packet() {
    delete[] packetData;
}

void Packet::copyPacketData(const uint8_t *inputData, uint8_t size) {
    for (uint8_t i = 0; i < size; i++) {
        this->packetData[i] = inputData[i];
    }
}

void Packet::copyPayload(const uint8_t *inputData, uint8_t size) {
    for (uint8_t i = 0; i < size; i++) {
        this->packetData[i + HEADER_SIZE] = inputData[i];
    }
}

void Packet::addCrc() {
    packetData[packetSize - 1] = CRC::calculate(packetData, packetSize - 1);
}

void Packet::reset() {
    index = 0;
}

bool Packet::hasNext() {
    return index < packetSize;
}

uint8_t Packet::next() {
    return packetData[index++];
}

bool Packet::checkCrc() {
    uint8_t packetCrc = packetData[packetSize - 1];
    uint8_t calculatedCrc = CRC::calculate(packetData, packetSize - 1);

    return packetCrc == calculatedCrc;
}
