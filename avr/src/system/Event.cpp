//
// Created by ghisi on 09.10.22.
//

#include "Event.h"

Event::Event(EventType type, void *data) {
    this->eType = type;
    this->dataPointer = data;
}

Event::~Event() {
    dataPointer = nullptr;
}

EventType Event::type() {
    return eType;
}

void *Event::data() {
    return dataPointer;
}

