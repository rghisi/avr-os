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
    bool handle(Message* event) override;

private:
    uint8_t dial = 0;
    MessageDispatcher *eventDispatcher;
    Dimmer *dimmer;
    void plus();
    void minus();
    static constexpr MessageType messageTypes[1] = {USER_INPUT};
    static constexpr uint8_t messageTypeCount = 1;
};


#endif //AVR_TEST_H
