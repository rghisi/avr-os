//
// Created by ghisi on 09.10.22.
//

#include <util/delay.h>
#include "EventLoop.h"
#include "../collections/BlockingQueue.cpp"
#include "HandlerMultiplexer.h"
#include "CpuStats.h"

EventLoop::EventLoop(SubscriberRegistry *subscriberRegistry, WallClock *wallClock) {
    this->subscriberRegistry = subscriberRegistry;
    this->wallClock = wallClock;
}

void EventLoop::process() {
    if (!events.empty()) {
        auto event = events.front();
        events.pop_front();
        auto *subscriber = subscriberRegistry->get(event->type());
        if (subscriber != nullptr) {
            auto userTimeStart = wallClock->now();
            subscriber->handle(event);
            CpuStats::eventLoopUserTime += wallClock->now() - userTimeStart;
        }
        delete event;
    }

}

bool EventLoop::push(Message* event) {
    if (events.size() <= BUFFER_SIZE) {
        events.push_back(event);
        return true;
    }

    return false;
}
