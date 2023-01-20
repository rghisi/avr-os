//
// Created by ghisi on 09.10.22.
//

#ifndef AVR_EVENTLOOP_H
#define AVR_EVENTLOOP_H


#include "Message.h"
#include "Subscriber.h"
#include "memory"
#include "list"
#include "any"
#include "SubscriberRegistry.h"
#include "WallClock.h"
#include "../collections/BlockingQueue.h"

class EventLoop {
public:
    EventLoop(SubscriberRegistry *subscriberRegistry, WallClock *wallClock);
    void process();
    bool push(Message* event);
private:
    static constexpr uint8_t BUFFER_SIZE = 10;
    BlockingQueue<Message*, BUFFER_SIZE> events;
    SubscriberRegistry *subscriberRegistry;
    WallClock *wallClock;
};


#endif //AVR_EVENTLOOP_H
