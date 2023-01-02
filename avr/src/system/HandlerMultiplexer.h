//
// Created by ghisi on 1/2/23.
//

#ifndef AVR_HANDLERMULTIPLEXER_H
#define AVR_HANDLERMULTIPLEXER_H

#include "MessageType.h"
#include "Subscriber.h"
#include "list"

class HandlerMultiplexer: public Subscriber {
public:
    ~HandlerMultiplexer();
    bool handle(Message* message) override;
    void add(Subscriber *handler);
private:
    std::list<Subscriber*> handlers;
};

#endif //AVR_HANDLERMULTIPLEXER_H
