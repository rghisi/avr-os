//
// Created by ghisi on 09.10.22.
//

#ifndef AVR_EVENT_H
#define AVR_EVENT_H

#include "EventType.h"
#include "memory"

class Event {
public:
    explicit Event(EventType type);
    virtual ~Event();
    EventType type();

private:
    EventType eType;
};


#endif //AVR_EVENT_H
