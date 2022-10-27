//
// Created by ghisi on 09.10.22.
//

#include <avr/io.h>
#include <util/delay.h>
#include "EventLoop.h"
#include "../collections/BlockingQueue.cpp"

EventLoop::EventLoop() {
    this->normalPriority = BlockingQueue<Event*, BUFFER_SIZE>();
    for (int i = 0; i < EventType::MAX; ++i) {
        handlers[i] = nullptr;
    }
}

bool EventLoop::push(Event *event) {
    normalPriority.offer(event);
    return true;
}

void EventLoop::addHandler(EventHandler *handler) {
    handlers[handler->type()] = handler;
}

void EventLoop::addHandler(EventHandler *handler, EventType eventType) {
    handlers[eventType] = handler;
}

bool EventLoop::process() {
    if (!normalPriority.isEmpty()) {
        auto *event = normalPriority.poll();
        auto *handler = handlers[event->type()];
        if (handler != nullptr) {
            handler->handle(event);
        }
        delete event;
        return true;
    }
    return false;
}
