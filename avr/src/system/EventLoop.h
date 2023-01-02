//
// Created by ghisi on 09.10.22.
//

#ifndef AVR_EVENTLOOP_H
#define AVR_EVENTLOOP_H


#include "Message.h"
#include "EventHandler.h"
#include "../collections/BlockingQueue.h"
#include "memory"
#include "list"
#include "any"

class EventLoop {
public:
    EventLoop();
    bool process();
    bool push(Message* event);
    void addHandler(EventHandler *handler);
private:
    static const uint8_t BUFFER_SIZE = 10;
    std::list<Message*> events;
    EventHandler* handlers[MessageType::MAX]{};
    uint16_t multiplexerBitmap = 0;
    void addHandler(EventHandler *handler, MessageType eventType);
    bool isMultiplexed(MessageType type) const;
    void setMultiplexed(MessageType type);
};


#endif //AVR_EVENTLOOP_H
