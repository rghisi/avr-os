//
// Created by ghisi on 09.10.22.
//

#include <avr/io.h>
#include <util/delay.h>
#include "EventLoop.h"
#include "../collections/BlockingQueue.cpp"

EventLoop::EventLoop() {
    for (int i = 0; i < EventType::MAX; ++i) {
        handlers[i] = nullptr;
    }
}

void EventLoop::addHandler(EventHandler *handler) {
    handlers[handler->type()] = handler;
}

void EventLoop::addHandler(EventHandler *handler, EventType eventType) {
    handlers[eventType] = handler;
}

bool EventLoop::process() {
    if (!events.empty()) {
        auto event = std::move(events.front());
        events.pop_front();
        auto *handler = handlers[event->type()];
        if (handler != nullptr) {
            handler->handle(std::move(event));
        }
        return true;
    }

    return false;
}

bool EventLoop::push(std::unique_ptr<Event> event) {
    if (events.size() <= BUFFER_SIZE) {
        events.push_back(std::move(event));
        return true;
    }

    return false;
}
