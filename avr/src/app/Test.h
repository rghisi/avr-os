//
// Created by ghisi on 12.12.22.
//

#ifndef AVR_TEST_H
#define AVR_TEST_H


#include "../system/EventHandler.h"
#include "../dimmer/Dimmer.h"
#include "../system/MessageDispatcher.h"

class Test: public EventHandler {
public:
    Test(MessageDispatcher *eventDispatcher, Dimmer *dimmer);
    MessageType eventType() override;
    bool handle(Message* event) override;

private:
    uint8_t dial = 0;
    MessageDispatcher *eventDispatcher;
    Dimmer *dimmer;

    void plus();

    void minus();
};


#endif //AVR_TEST_H
