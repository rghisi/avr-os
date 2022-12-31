//
// Created by ghisi on 17.10.22.
//

#ifndef AVR_DISPLAY_H
#define AVR_DISPLAY_H


#include "../system/EventHandler.h"

class Display: public EventHandler {
public:
    Display();
    EventType eventType() override;
    bool handle(Event* event) override;

private:
    void stats(Event* event);
    void text(Event* event);
    void memory(Event* event);
    void input(Event* event);
    void sensor(Event* event);
    uint8_t dial = 0;
};


#endif //AVR_DISPLAY_H
