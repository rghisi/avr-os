//
// Created by ghisi on 11.09.22.
//

#ifndef AVR_SENDER_H
#define AVR_SENDER_H

#include "Message.h"

class Sender {
public:
    virtual bool push(Message *message) = 0;
    virtual uint8_t getAddress() = 0;
};

#endif //AVR_SENDER_H
