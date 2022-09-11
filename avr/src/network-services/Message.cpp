//
// Created by ghisi on 11.09.22.
//

#include "Message.h"
#include "../collections/Array.cpp"

Message::Message(uint8_t destination, uint8_t source, uint8_t port, uint8_t *data, uint8_t dataSize) {
    this->source = source;
    this->destination = destination;
    this->port = port;
    this->size = dataSize + 1;
    this->serialized = new uint8_t[size];
    this->serialized[0] = port;
    Array<uint8_t>::copy(data, dataSize, serialized, 1);
}

Message::Message(uint8_t destination, uint8_t source, uint8_t *message, uint8_t size) {
    this->source = source;
    this->destination = destination;
    this->size = size;
    this->port = message[0];
    Array<uint8_t>::copy(message, size, serialized);
}

Message::~Message() {
    delete[] serialized;
}
