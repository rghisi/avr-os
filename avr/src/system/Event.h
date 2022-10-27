//
// Created by ghisi on 09.10.22.
//

#ifndef AVR_EVENT_H
#define AVR_EVENT_H

#include "EventType.h"
#include "EventPriority.h"

class Event {
public:
    Event(EventType type, void *data);
    Event(EventType type, EventPriority priority, void *data);
    ~Event();
    EventType type();
    EventPriority priority();
    void *data();

private:
    EventType eventType;
    EventPriority eventPriority;
    void *dataPointer;
};


#endif //AVR_EVENT_H
