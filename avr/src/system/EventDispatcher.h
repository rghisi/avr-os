//
// Created by ghisi on 09.10.22.
//

#ifndef AVR_EVENTDISPATCHER_H
#define AVR_EVENTDISPATCHER_H


#include "EventLoop.h"

class EventDispatcher {
public:
    explicit EventDispatcher(EventLoop *eventLoop);
    void dispatch(Event* event);
private:
    EventLoop *eventLoop;
};


#endif //AVR_EVENTDISPATCHER_H
