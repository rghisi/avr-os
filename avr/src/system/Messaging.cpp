//
// Created by ghisi on 09.10.22.
//

#include "Messaging.h"

Messaging::Messaging(EventLoop *eventLoop) {
    this->eventLoop = eventLoop;
}

void Messaging::send(Message* event) {
    this->eventLoop->push(event);
}
