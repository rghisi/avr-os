//
// Created by ghisi on 09.10.22.
//

#ifndef AVR_MESSAGING_H
#define AVR_MESSAGING_H


#include "EventLoop.h"

class Messaging {
public:
    explicit Messaging(EventLoop *eventLoop);
    void send(Message* event);
private:
    EventLoop *eventLoop;
};


#endif //AVR_MESSAGING_H
