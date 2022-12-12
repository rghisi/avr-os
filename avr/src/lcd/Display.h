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
    bool handle(std::unique_ptr<Event> event) override;

private:
    void stats(std::unique_ptr<Event> event);
    void text(std::unique_ptr<Event> event);
    void memory(std::unique_ptr<Event> event);
    void input(std::unique_ptr<Event> event);
    void sensor(std::unique_ptr<Event> event);
    uint8_t dial = 0;
};


#endif //AVR_DISPLAY_H
