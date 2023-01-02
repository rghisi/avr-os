//
// Created by ghisi on 09.10.22.
//

#include <util/delay.h>
#include "EventLoop.h"
#include "../collections/BlockingQueue.cpp"
#include "HandlerMultiplexer.h"

EventLoop::EventLoop(SubscriberRegistry *subscriberRegistry) {
    this->subscriberRegistry = subscriberRegistry;
}

bool EventLoop::process() {
    if (!events.empty()) {
        auto event = events.front();
        events.pop_front();
        auto *subscriber = subscriberRegistry->get(event->type());
        if (subscriber != nullptr) {
            subscriber->handle(event);
        }
        delete event;
        return true;
    }

    return false;
}

bool EventLoop::push(Message* event) {
    if (events.size() <= BUFFER_SIZE) {
        events.push_back(event);
        return true;
    }

    return false;
}
