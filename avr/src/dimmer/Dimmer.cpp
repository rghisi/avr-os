//
// Created by ghisi on 20.11.22.
//

#include "Dimmer.h"
#include "avr/io.h"

Dimmer::Dimmer(Timer1 *timer1, ExternalInterrupt *externalInterrupt) {
    this->timer = timer1;
    this->externalInterrupt = externalInterrupt;
}

void Dimmer::calibrate() {
    state = State::CALIBRATING_WAITING_ZERO_CROSS_START;
    externalInterrupt->externalInterruptOnFallingEdge();
}

void Dimmer::handleExternalInterrupt() {
    processState();
}

void Dimmer::handleTimerCompareMatchInterrupt() {
    processState();
}

void Dimmer::processState() {
    switch (state) {
        case State::CALIBRATING_WAITING_ZERO_CROSS_START:
            timer->timer1CompareMatchA(UINT16_MAX);
            timer->timer1DoNothingOnCompareMatchA();
            timer->startTimer1();
            externalInterrupt->externalInterruptOnRisingEdge();
            state = State::CALIBRATING_WAITING_ZERO_CROSS_END;
            break;
        case State::CALIBRATING_WAITING_ZERO_CROSS_END:
            timeToZeroCross = timer->timer1Value() >> 1; //divide by two
            externalInterrupt->externalInterruptOnFallingEdge();
            state = State::CALIBRATING_WAITING_HALF_WAVE_END;
            break;
        case State::CALIBRATING_WAITING_HALF_WAVE_END:
            timer->stopTimer1();
            externalInterrupt->externalInterruptDisable();
            halfWaveLength = timer->timer1Value();
            positionStep = (halfWaveLength - PULSE_LENGTH) >> 8; //divide by 256
            state = State::DISABLED;
            break;
        case State::WAITING_ZERO_CROSS_START:
            timer->timer1CompareMatchA(timeToZeroCross);
            timer->timer1DoNothingOnCompareMatchA();
            timer->startTimer1();
            state = State::WAITING_PULSE_START;
            break;
        case State::WAITING_PULSE_START:
            timer->stopTimer1();
            timer->timer1CompareMatchA(position);
            timer->timer1SetOnCompareMatchA();
            timer->startTimer1();
            state = State::WAITING_PULSE_END;
            break;
        case State::WAITING_PULSE_END:
            timer->stopTimer1();
            timer->timer1CompareMatchA(PULSE_LENGTH);
            timer->timer1ClearOnCompareMatchA();
            timer->startTimer1();
            state = State::PULSE_ENDED;
            break;
        case State::PULSE_ENDED:
            timer->stopTimer1();
            state = State::WAITING_ZERO_CROSS_START;
            break;
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
    externalInterrupt->externalInterruptDisable();
    timer->stopTimer1();
    timer->timer1DoNothingOnCompareMatchA();
    state = State::DISABLED;
}

void Dimmer::setPosition(uint8_t nposition) {
    this->position = (UINT8_MAX - nposition) * positionStep;
}


