//
// Created by ghisi on 1/10/23.
//

#include "Fan.h"
#include "FanCommand.h"
#include <avr/io.h>

void Fan::setup() {
    DDRB |= _BV(PORTB3);
    PORTB &= ~_BV(PORTB3);
    TCCR2A |= _BV(COM2A1) | _BV(WGM20);
    TCCR2B |= _BV(CS22);
    OCR2A = 0x00;
}

void Fan::handle(Message *message) {
    if (message->type() == FAN_COMMAND) {
        auto command = static_cast<FanCommand*>(message);
        if (command->power == 0) {
            off();
        } else {
            on(command->power);
        }
    }
}

void Fan::off() {
    PORTB &= ~_BV(PORTB3);
    OCR2A = 0;
}

void Fan::on(uint8_t power) {
    PORTB |= _BV(PORTB3);
    OCR2A = power;
}
