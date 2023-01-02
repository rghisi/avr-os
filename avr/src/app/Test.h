//
// Created by ghisi on 12.12.22.
//

#ifndef AVR_TEST_H
#define AVR_TEST_H


#include "../system/EventHandler.h"
#include "../dimmer/Dimmer.h"
#include "../system/Messaging.h"
#include "Application.h"

class Test: public EventHandler, public Application {
public:
    Test(Messaging *eventDispatcher, Dimmer *dimmer);
    bool handle(Message* event) override;
    void toForeground() override;
    void toBackground() override;

private:
    uint8_t dial = 0;
    Messaging *eventDispatcher;
    Dimmer *dimmer;
    void plus();
    void minus();
    static constexpr MessageType messageTypes[1] = {USER_INPUT};
    static constexpr uint8_t messageTypeCount = 1;

    void renderUI();
};


#endif //AVR_TEST_H
