//
// Created by ghisi on 09.10.22.
//

#ifndef AVR_EVENTDISPATCHER_H
#define AVR_EVENTDISPATCHER_H


#include "EventLoop.h"
#include "memory"

class EventDispatcher {
public:
    explicit EventDispatcher(EventLoop *eventLoop);
    void dispatch(std::unique_ptr<Event> event);
private:
    EventLoop *eventLoop;
};


#endif //AVR_EVENTDISPATCHER_H
