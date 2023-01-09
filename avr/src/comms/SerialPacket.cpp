//
// Created by ghisi on 1/9/23.
//

#include "SerialPacket.h"

SerialPacket::SerialPacket(uint8_t *bytes, uint8_t length) : Message(MessageType::SERIAL_SEND) {
    this->bytes = bytes;
    this->length = length;
}

SerialPacket::~SerialPacket() {
    delete bytes;
}
