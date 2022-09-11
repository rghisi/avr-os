//
// Created by ghisi on 11.09.22.
//

#ifndef AVR_RECEIVER_H
#define AVR_RECEIVER_H

#include "Message.h"

class Receiver {
public:
    virtual void receive(Message *message) = 0;
    virtual uint8_t getPort() {
        return 0;
    }
};

#endif //AVR_RECEIVER_H
