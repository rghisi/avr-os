//
// Created by ghisi on 09.10.22.
//

#include "Event.h"

Event::Event(EventType type) {
    this->eType = type;
}

Event::~Event() = default;

EventType Event::type() {
    return eType;
}

