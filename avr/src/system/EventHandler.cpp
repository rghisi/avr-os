//
// Created by ghisi on 1/1/23.
//

#include "EventHandler.h"

EventHandler::EventHandler(const MessageType *types, const uint8_t size) {
    this->types = types;
    this->size = size;
}

const MessageType * EventHandler::messageTypes() {
    return types;
}

uint8_t EventHandler::messageTypeCount() const {
    return size;
}
