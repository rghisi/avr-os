//
// Created by ghisi on 12.12.22.
//

#ifndef AVR_TEST_H
#define AVR_TEST_H


#include "../system/Subscriber.h"
#include "../dimmer/Dimmer.h"
#include "../system/Messaging.h"
#include "Application.h"

class Test: public Subscriber, public Application {
public:
    Test(Messaging *eventDispatcher, Dimmer *dimmer);
    void handle(Message* event) override;
    void toForeground() override;
    void toBackground() override;

    char *title() override;

private:
    uint8_t dial = 0;
    Messaging *eventDispatcher;
    Dimmer *dimmer;
    void plus();
    void minus();
    void renderUI();
};


#endif //AVR_TEST_H
