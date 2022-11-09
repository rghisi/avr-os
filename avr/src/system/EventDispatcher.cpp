//
// Created by ghisi on 09.10.22.
//

#include <avr/io.h>
#include "EventDispatcher.h"

EventDispatcher::EventDispatcher(EventLoop *eventLoop) {
    this->eventLoop = eventLoop;
}

void EventDispatcher::dispatch(std::unique_ptr<Event> event) {
    this->eventLoop->push(std::move(event));
}
