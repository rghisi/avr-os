//
// Created by ghisi on 12.12.22.
//

#ifndef AVR_USERINPUT_H
#define AVR_USERINPUT_H


#include "cstdint"

class UserInput {
public:
    enum class Event {
        DIAL_PLUS,
        DIAL_MINUS,
        DIAL_BUTTON_PRESSED,
        DIAL_BUTTON_RELEASED,
        BUTTON_LEFT_PRESSED,
        BUTTON_LEFT_RELEASED,
        BUTTON_UP_PRESSED,
        BUTTON_UP_RELEASED,
        BUTTON_RIGHT_PRESSED,
        BUTTON_RIGHT_RELEASED,
        BUTTON_DOWN_PRESSED,
        BUTTON_DOWN_RELEASED,
        BUTTON_ENTER_PRESSED,
        BUTTON_ENTER_RELEASED,
        NONE
    };
    explicit UserInput(Event event, uint16_t value);
    Event event;
    uint16_t value;
};


#endif //AVR_USERINPUT_H
