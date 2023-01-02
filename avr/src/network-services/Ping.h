//
// Created by ghisi on 11.09.22.
//

#ifndef AVR_PING_H
#define AVR_PING_H


#include "PacketReceiver.h"
#include "PacketSender.h"
#include "../system/EventHandler.h"
#include "../system/Messaging.h"

class Ping: public EventHandler {
public:
    explicit Ping(EventDispatcher *eventDispatcher);
    void ping(uint8_t destination);
    void pong(uint8_t destination);
    bool handle(std::unique_ptr<Event> event) override;
    EventType type() override;
private:
    bool isPing(Packet *packet);
    static const uint8_t SERVICE = 0x01;
    uint8_t pingMessage[4] = {'P', 'I', 'N', 'G'};
    uint8_t pongMessage[4] = {'P', 'O', 'N', 'G'};
    EventDispatcher *eventDispatcher;
};


#endif //AVR_PING_H
