//
// Created by ghisi on 11.09.22.
//

#ifndef AVR_PING_H
#define AVR_PING_H


#include "Receiver.h"
#include "Sender.h"

class Ping: public Receiver {
public:
    Ping(Sender *sender);
    void ping(uint8_t destination);
    void receive(Message *message) override;
    uint8_t getPort() override;
private:
    static const uint8_t PORT = 0x01;
    Sender *sender;
};


#endif //AVR_PING_H
