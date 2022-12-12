//
// Created by ghisi on 12.12.22.
//

#ifndef AVR_USERINPUT_H
#define AVR_USERINPUT_H


class UserInput {
public:
    enum class Event {
        DIAL_PLUS, DIAL_MINUS, DIAL_BUTTON_PRESSED, DIAL_BUTTON_RELEASED
    };
    explicit UserInput(Event event);
    Event event;
};


#endif //AVR_USERINPUT_H
