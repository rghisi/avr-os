//
// Created by ghisi on 09.10.22.
//

#ifndef AVR_EVENTLOOP_H
#define AVR_EVENTLOOP_H


#include "Event.h"
#include "EventHandler.h"
#include "../collections/BlockingQueue.h"
#include "memory"
#include "list"
#include "any"

class EventLoop {
public:
    EventLoop();
    bool process();
    bool push(std::unique_ptr<Event> event);
    void addHandler(EventHandler *handler);
    void addHandler(EventHandler *handler, EventType eventType);
private:
    static const uint8_t BUFFER_SIZE = 10;
    std::list<std::unique_ptr<Event>> events;
    EventHandler* handlers[EventType::MAX]{};
};


#endif //AVR_EVENTLOOP_H
