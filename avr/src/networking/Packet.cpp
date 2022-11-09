/*
 * Frame.cpp
 *
 *  Created on: Aug 27, 2022
 *      Author: ghisi
 */

#include "Packet.h"
#include "../std/CRC.h"

Packet::Packet(uint8_t destination, uint8_t source, uint16_t id, uint8_t service, std::unique_ptr<uint8_t[]> payload, uint8_t payloadLength) {
    this->destinationAddress = destination;
    this->sourceAddress = source;
    this->packetLength = payloadLength + HEADER_SIZE;
    this->packetId = id;
    this->serviceId = service;
    this->payloadBytes = std::move(payload);
    this->packetCrc = calculateCrc();
}

Packet::Packet(uint8_t destination, uint8_t source, uint16_t id, uint8_t service, uint8_t crc, std::unique_ptr<uint8_t[]> payload, uint8_t payloadLength) {
    this->destinationAddress = destination;
    this->sourceAddress = source;
    this->packetLength = payloadLength + HEADER_SIZE;
    this->packetId = id;
    this->serviceId = service;
    this->packetCrc = crc;
    this->payloadBytes = std::move(payload);
}

uint8_t Packet::source() const {
    return sourceAddress;
}

uint8_t Packet::destination() const {
    return destinationAddress;
}

uint8_t Packet::length() const {
    return packetLength;
}

uint16_t Packet::id() const {
    return packetId;
}

uint8_t Packet::service() const {
    return serviceId;
}

uint8_t Packet::crc() const {
    return packetCrc;
}

uint8_t Packet::payloadLength() const {
    return packetLength - HEADER_SIZE;
}

uint8_t *Packet::payload() {
    return payloadBytes.get();
}

bool Packet::isValid() {
    return packetCrc == calculateCrc();
}

uint8_t Packet::calculateCrc() {
    auto crc = CRC();
    crc.add(PACKET_START_SYMBOL);
    crc.add(destinationAddress);
    crc.add(sourceAddress);
    crc.add(packetLength);
    crc.add((uint8_t ) (packetId >> 8));
    crc.add((uint8_t ) packetId);
    crc.add(serviceId);
    uint8_t length = payloadLength();
    for (int i = 0; i < length; ++i) {
        crc.add(payloadBytes[i]);
    }

    return crc.value();
}
