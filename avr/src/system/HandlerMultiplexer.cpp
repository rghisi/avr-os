//
// Created by ghisi on 1/2/23.
//

#include "HandlerMultiplexer.h"

HandlerMultiplexer::HandlerMultiplexer() : EventHandler(nullptr, 0) {
    type = MAX;
}

HandlerMultiplexer::~HandlerMultiplexer() = default;

bool HandlerMultiplexer::handle(Message *message) {
    for (auto handler: handlers) {
        handler->handle(message);
    }
    return true;
}

void HandlerMultiplexer::add(EventHandler *handler) {
    this->handlers.push_back(handler);
}
