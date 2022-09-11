//
// Created by ghisi on 11.09.22.
//

#include "Ping.h"

Ping::Ping(Sender *sender) {
    this->sender = sender;
}

void Ping::ping(uint8_t destination) {
    uint8_t data[] = {'P', 'I', 'N', 'G'};
    uint8_t size = sizeof(data);
    auto *ping = new Message(destination, sender->getAddress(), Ping::PORT, data, size);
    bool success = sender->push(ping);
}

void Ping::receive(Message *message) {
    uint8_t data[] = {'P', 'O', 'N', 'G'};
    uint8_t size = sizeof(data);
    auto *pong = new Message(message->source, sender->getAddress(), Ping::PORT, data, size);
    bool success = sender->push(pong);
    delete message;
}

uint8_t Ping::getPort() {
    return Ping::PORT;
}
