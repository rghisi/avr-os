//
// Created by ghisi on 1/2/23.
//

#include "HandlerMultiplexer.h"

HandlerMultiplexer::~HandlerMultiplexer() = default;

void HandlerMultiplexer::handle(Message *message) {
    for (auto handler: handlers) {
        handler->handle(message);
    }
}

void HandlerMultiplexer::add(Subscriber *handler) {
    this->handlers.push_back(handler);
}
