//
// Created by ghisi on 11.09.22.
//

#ifndef AVR_MESSAGE_H
#define AVR_MESSAGE_H


#include "cstdint"

class Message {
public:
    Message(uint8_t destination, uint8_t source, uint8_t port, uint8_t *data, uint8_t dataSize);

    Message(uint8_t destination, uint8_t source, uint8_t *message, uint8_t size);

    ~Message();
    uint8_t destination;
    uint8_t source;
    uint8_t port;
    uint8_t size;
    uint8_t *serialized;
};


#endif //AVR_MESSAGE_H
