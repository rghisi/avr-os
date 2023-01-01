//
// Created by ghisi on 30.10.22.
//

#include <avr/io.h>
#include "KeyPad.h"
#include "UserInput.h"

KeyPad::KeyPad(MessageDispatcher *eventDispatcher) {
    this->eventDispatcher = eventDispatcher;
    previous = Key::RELEASED;
}

void KeyPad::run() {
    uint16_t value = ADC;
    Key current = Key::RELEASED;
    if (value > 1000) {
        current = Key::RELEASED;
    } else if (value < 34 && value >= 28) {
        current = Key::UP;
    } else if (value < 95 && value >= 80) {
        current = Key::DOWN;
    } else if (value < 20 && value >= 0) {
        current = Key::LEFT;
    } else if (value < 170 && value >= 160) {
        current = Key::RIGHT;
    } else if (value < 360 && value >= 340) {
        current = Key::ENTER;
    }
    if (current != previous) {
        UserInput::UserInputEvent button = UserInput::UserInputEvent::NONE;
        switch (current) {
            case Key::RELEASED:
                switch (previous) {
                    case Key::UP:
                        button = UserInput::UserInputEvent::BUTTON_UP_RELEASED;
                        break;
                    case Key::DOWN:
                        button = UserInput::UserInputEvent::BUTTON_DOWN_RELEASED;
                        break;
                    case Key::LEFT:
                        button = UserInput::UserInputEvent::BUTTON_LEFT_RELEASED;
                        break;
                    case Key::RIGHT:
                        button = UserInput::UserInputEvent::BUTTON_RIGHT_RELEASED;
                        break;
                    case Key::ENTER:
                        button = UserInput::UserInputEvent::BUTTON_ENTER_RELEASED;
                        break;
                    default:
                        break;
                }
                break;
            case Key::UP:
                button = UserInput::UserInputEvent::BUTTON_UP_PRESSED;
                break;
            case Key::DOWN:
                button = UserInput::UserInputEvent::BUTTON_DOWN_PRESSED;
                break;
            case Key::LEFT:
                button = UserInput::UserInputEvent::BUTTON_LEFT_PRESSED;
                break;
            case Key::RIGHT:
                button = UserInput::UserInputEvent::BUTTON_RIGHT_PRESSED;
                break;
            case Key::ENTER:
                button = UserInput::UserInputEvent::BUTTON_ENTER_PRESSED;
                break;
        }
        if (button != UserInput::UserInputEvent::NONE) {
            auto event = new UserInput(button, value);
            eventDispatcher->dispatch(event);
        }
        previous = current;
    }
}

uint32_t KeyPad::delay() {
    return 50;
}

Task::Type KeyPad::type() {
    return Type::PERIODIC;
}

void KeyPad::setup() {
    DDRC &= ~_BV(PORTC0);
    DIDR0 = _BV(ADC0D);
    ADMUX = _BV(REFS0); //AVcc reference
    ADCSRA = _BV(ADEN) | _BV(ADATE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
    ADCSRB = 0x00;
    ADCSRA |= _BV(ADSC);
}
