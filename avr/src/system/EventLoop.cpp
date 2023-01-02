//
// Created by ghisi on 09.10.22.
//

#include <util/delay.h>
#include "EventLoop.h"
#include "../collections/BlockingQueue.cpp"
#include "HandlerMultiplexer.h"

EventLoop::EventLoop() {
    for (int i = 0; i < MessageType::MAX; ++i) {
        handlers[i] = nullptr;
    }
}

void EventLoop::addHandler(EventHandler *handler) {
    for (uint8_t i = 0; i < handler->messageTypeCount(); i++) {
        auto messageType = handler->messageTypes()[i];
        addHandler(handler, messageType);
    }
}

void EventLoop::addHandler(EventHandler *handler, MessageType eventType) {
    auto registered = handlers[eventType];
    if (registered == nullptr) {
        handlers[eventType] = handler;
    } else {
        if (isMultiplexed(eventType)) {
            auto multiplexer = static_cast<HandlerMultiplexer*>(registered);
            multiplexer->add(handler);
        } else {
            auto multiplexer = new HandlerMultiplexer();
            multiplexer->add(registered);
            multiplexer->add(handler);
            handlers[eventType] = multiplexer;
            setMultiplexed(eventType);
        }
    }
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

void EventLoop::setMultiplexed(MessageType type) {
    multiplexerBitmap |= 0x01 << (uint8_t)type;
}

bool EventLoop::isMultiplexed(MessageType type) const {
    return 0x01 & (multiplexerBitmap >> (uint8_t)type);
}