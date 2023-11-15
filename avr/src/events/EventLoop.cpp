//
// Created by ghisi on 09.10.22.
//

#include "EventLoop.h"
#include "HandlerMultiplexer.h"

EventLoop::EventLoop(SubscriberRegistry *subscriberRegistry, WallClock *wallClock) {
    this->subscriberRegistry = subscriberRegistry;
    this->wallClock = wallClock;
}

void EventLoop::process() {
    if (!events.isEmpty()) {
        auto event = events.poll();
        if (event) {
            auto *subscriber = subscriberRegistry->get(event->type());
            if (subscriber != nullptr) {
                subscriber->handle(event);
            }
        }
        delete event;
    }
}

bool EventLoop::push(Message* event) {
    return events.offer(event);
}
