//
// Created by ghisi on 1/10/23.
//

#include <avr/io.h>
#include "Buzzer.h"
#include "BuzzerCommand.h"
#include "../../system/AsyncChain.h"

Buzzer::Buzzer(Messaging *messaging) {
    this->messaging = messaging;
}

void Buzzer::setup() {
    DDRC |= _BV(PORTC0);
    PORTC &= ~_BV(PORTC0);
}

void Buzzer::handle(Message *message) {
    if (message->type() == MessageType::BUZZER) {
        auto command = static_cast<BuzzerCommand*>(message);
        auto async = new AsyncChain(messaging);
        async->then([](){Buzzer::on();})
        ->wait(command->duration * 10)
        ->then([](){Buzzer::off();})
        ->schedule();
    }
}

void Buzzer::on() {
    PORTC |= _BV(PORTC0);
}

void Buzzer::off() {
    PORTC &= ~_BV(PORTC0);
}


