//
// Created by ghisi on 30.10.22.
//

#include <avr/io.h>
#include <util/delay.h>
#include "KeyPad.h"

KeyPad::KeyPad(EventDispatcher *eventDispatcher) {
    this->eventDispatcher = eventDispatcher;
}

void KeyPad::run() {
    PORTB ^= _BV(PORTB5);
//    uint16_t value = ADC;
//    button = Key::IDLE;
//    if (value < 965 && value > 945) {
//        button = Key::UP;
//    } else if (value < 915 && value > 900) {
//        button = Key::DOWN;
//    } else if (value < 1010 && value > 980) {
//        button = Key::LEFT;
//    } else if (value < 850 && value > 820) {
//        button = Key::RIGHT;
//    } else if (value < 670 && value > 640) {
//        button = Key::CENTER;
//    }
//    auto event = std::make_unique<Event>(KEYPAD_KEY_DOWN, &button);
//    eventDispatcher->dispatch(std::move(event));
}

uint32_t KeyPad::delay() {
    return 50;
}

Task::Type KeyPad::type() {
    return Type::PERIODIC;
}
