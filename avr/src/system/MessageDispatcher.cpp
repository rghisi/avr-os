//
// Created by ghisi on 09.10.22.
//

#include "MessageDispatcher.h"

MessageDispatcher::MessageDispatcher(EventLoop *eventLoop) {
    this->eventLoop = eventLoop;
}

void MessageDispatcher::dispatch(Message* event) {
    this->eventLoop->push(event);
}
