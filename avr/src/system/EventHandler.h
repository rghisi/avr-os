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
    EventHandler(const MessageType *types, uint8_t size);
    virtual bool handle(Message* event) = 0;
    virtual const MessageType * messageTypes();
    [[nodiscard]] virtual uint8_t messageTypeCount() const;
private:
    uint8_t size;
    const MessageType *types;
};



#endif //AVR_EVENTHANDLER_H
