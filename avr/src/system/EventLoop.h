//
// Created by ghisi on 09.10.22.
//

#ifndef AVR_EVENTLOOP_H
#define AVR_EVENTLOOP_H


#include "Event.h"
#include "EventHandler.h"
#include "../collections/BlockingQueue.h"

class EventLoop {
public:
    EventLoop();
    bool process();
    bool push(Event *event);
    void addHandler(EventHandler *handler);
    void addHandler(EventHandler *handler, EventType eventType);
private:
    static const uint8_t BUFFER_SIZE = 10;
    BlockingQueue<Event*, BUFFER_SIZE> normalPriority;
    EventHandler* handlers[EventType::MAX]{};
};


#endif //AVR_EVENTLOOP_H
