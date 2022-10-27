//
// Created by ghisi on 09.10.22.
//

#include "Event.h"

Event::Event(EventType type, void *data): Event(type, EventPriority::NORMAL, data) {}

Event::Event(EventType type, EventPriority priority, void *data) {
    this->eventType = type;
    this->dataPointer = data;
    this->eventPriority = priority;
}

Event::~Event() {
    dataPointer = nullptr;
}

EventType Event::type() {
    return eventType;
}

EventPriority Event::priority() {
    return eventPriority;
}

void *Event::data() {
    return dataPointer;
}
