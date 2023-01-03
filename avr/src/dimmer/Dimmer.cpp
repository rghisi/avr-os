//
// Created by ghisi on 20.11.22.
//

#include "Dimmer.h"
#include "avr/io.h"
#include "../system/Math.h"

Dimmer::Dimmer(Timer1 *timer1, ExternalInterrupt *externalInterrupt) {
    this->timer = timer1;
    this->externalInterrupt = externalInterrupt;
    this->disable();
    this->setPosition(0);
}

void Dimmer::handleExternalInterrupt() {
    switch (state) {
        case State::WAITING_ZERO_CROSS_START:
            timer->timer1ForceCompareMatchA();
            timer->stopTimer1();
            timer->timer1CompareMatchA(timeToZeroCross + delay);
            timer->timer1SetOnCompareMatchA();
            timer->startTimer1();
            state = State::WAITING_PULSE_START;
            break;
        default:
            return;
    }
}

void Dimmer::handleTimerCompareMatchInterrupt() {
    switch (state) {
        case State::WAITING_PULSE_START:
            timer->timer1CompareMatchA(PULSE_LENGTH);
            timer->timer1ClearOnCompareMatchA();
            state = State::WAITING_PULSE_END;
            break;
        case State::WAITING_PULSE_END:
            state = State::WAITING_ZERO_CROSS_START;
        default:
            return;
    }
}

void Dimmer::enable() {
    if (state == State::DISABLED) {
        externalInterrupt->externalInterruptOnFallingEdge();
        state = State::WAITING_ZERO_CROSS_START;
    }
}

void Dimmer::disable() {
    if (state != State::DISABLED) {
        externalInterrupt->externalInterruptDisable();
        timer->resetTimer1();
        timer->stopTimer1();
        timer->timer1ClearOnCompareMatchA();
        timer->timer1ForceCompareMatchA();
        timer->timer1DoNothingOnCompareMatchA();
        state = State::DISABLED;
    }
}

void Dimmer::setPosition(uint16_t position) {
    this->delay = MAX_DELAY - Math::min(position, MAX_DELAY);
}

uint16_t Dimmer::getPosition() {
    return MAX_DELAY - delay;
}


