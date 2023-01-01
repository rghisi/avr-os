//
// Created by ghisi on 09.10.22.
//

#ifndef AVR_MESSAGEDISPATCHER_H
#define AVR_MESSAGEDISPATCHER_H


#include "EventLoop.h"

class MessageDispatcher {
public:
    explicit MessageDispatcher(EventLoop *eventLoop);
    void dispatch(Message* event);
private:
    EventLoop *eventLoop;
};


#endif //AVR_MESSAGEDISPATCHER_H
