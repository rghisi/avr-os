//
// Created by ghisi on 09.10.22.
//

#include <avr/io.h>
#include <util/delay.h>
#include "EventLoop.h"
#include "../collections/BlockingQueue.cpp"

EventLoop::EventLoop() {
    for (int i = 0; i < MessageType::MAX; ++i) {
        handlers[i] = nullptr;
    }
}

void EventLoop::addHandler(EventHandler *handler) {
    handlers[handler->eventType()] = handler;
}

void EventLoop::addHandler(EventHandler *handler, MessageType eventType) {
    handlers[eventType] = handler;
}

bool EventLoop::process() {
    if (!events.empty()) {
        auto event = events.front();
        events.pop_front();
        auto *handler = handlers[event->type()];
        if (handler != nullptr) {
            handler->handle(event);
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
