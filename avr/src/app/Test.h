//
// Created by ghisi on 12.12.22.
//

#ifndef AVR_TEST_H
#define AVR_TEST_H


#include "../system/EventHandler.h"
#include "../dimmer/Dimmer.h"
#include "../system/EventDispatcher.h"

class Test: public EventHandler {
public:
    Test(EventDispatcher *eventDispatcher, Dimmer *dimmer);
    EventType eventType() override;
    bool handle(std::unique_ptr<Event> event) override;

private:
    uint8_t dial = 0;
    EventDispatcher *eventDispatcher;
    Dimmer *dimmer;

    void plus();

    void minus();
};


#endif //AVR_TEST_H
