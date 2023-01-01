//
// Created by ghisi on 09.10.22.
//

#ifndef AVR_EVENTHANDLER_H
#define AVR_EVENTHANDLER_H

#include "memory"
#include "MessageType.h"
#include "Message.h"

class EventHandler {
public:
    virtual MessageType eventType() = 0;
    virtual bool handle(Message* event) = 0;
};


#endif //AVR_EVENTHANDLER_H
