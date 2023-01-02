//
// Created by ghisi on 1/2/23.
//

#include "HandlerMultiplexer.h"

HandlerMultiplexer::~HandlerMultiplexer() = default;

bool HandlerMultiplexer::handle(Message *message) {
    for (auto handler: handlers) {
        handler->handle(message);
    }
    return true;
}

void HandlerMultiplexer::add(Subscriber *handler) {
    this->handlers.push_back(handler);
}
