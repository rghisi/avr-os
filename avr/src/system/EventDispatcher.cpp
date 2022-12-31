//
// Created by ghisi on 09.10.22.
//

#include "EventDispatcher.h"

EventDispatcher::EventDispatcher(EventLoop *eventLoop) {
    this->eventLoop = eventLoop;
}

void EventDispatcher::dispatch(Event* event) {
    this->eventLoop->push(event);
}
