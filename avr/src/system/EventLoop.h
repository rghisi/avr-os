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

class EventLoop {
public:
    EventLoop(SubscriberRegistry *subscriberRegistry);
    bool process();
    bool push(Message* event);
private:
    static const uint8_t BUFFER_SIZE = 10;
    std::list<Message*> events;
    SubscriberRegistry *subscriberRegistry;
};


#endif //AVR_EVENTLOOP_H
