//
// Created by ghisi on 17.10.22.
//

#ifndef AVR_DISPLAY_H
#define AVR_DISPLAY_H


#include "../system/EventHandler.h"

class Display: public EventHandler {
public:
    Display();
    EventType type() override;
    bool handle(Event *event) override;
private:
    void stats(Event *event);
    void text(Event *event);

    void memory(Event *pEvent);
};


#endif //AVR_DISPLAY_H
