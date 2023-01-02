//
// Created by ghisi on 1/2/23.
//

#ifndef AVR_HANDLERMULTIPLEXER_H
#define AVR_HANDLERMULTIPLEXER_H

#include "MessageType.h"
#include "EventHandler.h"
#include "list"

class HandlerMultiplexer: public EventHandler {
public:
    HandlerMultiplexer();
    ~HandlerMultiplexer();
    bool handle(Message* message) override;
    void add(EventHandler *handler);
private:
    MessageType type;
    std::list<EventHandler*> handlers;
};

#endif //AVR_HANDLERMULTIPLEXER_H
