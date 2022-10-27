//
// Created by ghisi on 09.10.22.
//

#ifndef AVR_EVENTHANDLER_H
#define AVR_EVENTHANDLER_H


#include "EventType.h"
#include "Event.h"

class EventHandler {
public:
    virtual EventType type() = 0;
    virtual bool handle(Event *event) = 0;
};


#endif //AVR_EVENTHANDLER_H
