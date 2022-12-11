//
// Created by ghisi on 09.11.22.
//

#include <avr/interrupt.h>
#include "ATMega328P.h"

Timer0InterruptHandler *ATMega328P::timer0InterruptHandler = nullptr;
TimerCompareMatchInterruptHandler *ATMega328P::timer1CompareMatchAInterruptHandler = nullptr;
TimerCompareMatchInterruptHandler *ATMega328P::timer1CompareMatchBInterruptHandler = nullptr;
ExternalInterruptHandler *ATMega328P::externalInterruptHandler = nullptr;

ATMega328P::ATMega328P() {
}

void ATMega328P::setTimer0InterruptHandler(Timer0InterruptHandler *handler) {
    ATMega328P::timer0InterruptHandler = handler;
}

void ATMega328P::enableInterrupts() {
    sei();
}

void ATMega328P::disableInterrupts() {
    cli();
}

void ATMega328P::setupTimer0() {
    TCCR0A = _BV(WGM01);
    TCCR0B = _BV(CS01) | _BV(CS00);
    TCNT0 = 0;
    OCR0A = 250;
    TIMSK0 = _BV(OCIE0A);
}

void ATMega328P::setupTimer1() {
    DDRB |= _BV(PORTB2) | _BV(PORTB1);
    PORTB &= ~(_BV(PORTB2) | _BV(PORTB1));

    TCCR1A = 0;
    TCCR1B = _BV(WGM12);
    TCNT1 = 0;
//    OCR1A = 1000;
//    OCR1B = 2000;
    TIMSK1 = _BV(OCIE1B) | _BV(OCIE1A);
}

void ATMega328P::setTimer1CompareMatchAInterruptHandler(TimerCompareMatchInterruptHandler *handler) {
    timer1CompareMatchAInterruptHandler = handler;
}

void ATMega328P::setTimer1CompareMatchBInterruptHandler(TimerCompareMatchInterruptHandler *handler) {
    timer1CompareMatchBInterruptHandler = handler;
}

void ATMega328P::startTimer1() {
    TCNT1 = 0;
    TCCR1B |= _BV(CS11) | _BV(CS10); //Clock with CLK/64 prescaler
}

void ATMega328P::stopTimer1() {
    TCCR1B &= ~(_BV(CS11) | _BV(CS10)); //No clock
}

void ATMega328P::timer1CompareMatchA(uint16_t value) {
    OCR1A = value;
}

void ATMega328P::timer1CompareMatchB(uint16_t value) {
    OCR1B = value;
}

void ATMega328P::setupExternalInterrupt() {
    DDRD &= ~_BV(PORTD2);
}

void ATMega328P::setExternalInterruptHandler(ExternalInterruptHandler *handler) {
    ATMega328P::externalInterruptHandler = handler;
}

void TIMER0_COMPA_vect(void) {
    if (ATMega328P::timer0InterruptHandler != nullptr) {
        ATMega328P::timer0InterruptHandler->processTick();
    }
}

void TIMER1_COMPA_vect(void) {
    if (ATMega328P::timer1CompareMatchAInterruptHandler != nullptr) {
        ATMega328P::timer1CompareMatchAInterruptHandler->handleTimerCompareMatchInterrupt();
    }
}

void TIMER1_COMPB_vect(void) {
    if (ATMega328P::timer1CompareMatchBInterruptHandler != nullptr) {
        ATMega328P::timer1CompareMatchBInterruptHandler->handleTimerCompareMatchInterrupt();
    }
}

void INT0_vect(void) {
    if (ATMega328P::externalInterruptHandler != nullptr) {
        ATMega328P::externalInterruptHandler->handleExternalInterrupt();
    }
}

void ATMega328P::timer1ClearOnCompareMatchA() {
    TCCR1A &= ~(_BV(COM1A0));
    TCCR1A |= _BV(COM1A1);
}

void ATMega328P::timer1SetOnCompareMatchA() {
    TCCR1A |= _BV(COM1A1) | _BV(COM1A0);
}

void ATMega328P::timer1DoNothingOnCompareMatchA() {
    TCCR1A &= ~(_BV(COM1A1) | _BV(COM1A0));
}

void ATMega328P::externalInterruptOnFallingEdge() {
    EICRA &= ~_BV(ISC00);
    EICRA |= _BV(ISC01);
    EIMSK |= _BV(INT0);
}

void ATMega328P::externalInterruptOnRisingEdge() {
    EICRA |= _BV(ISC01) | _BV(ISC00);
    EIMSK |= _BV(INT0);
}

void ATMega328P::externalInterruptDisable() {
    EIMSK &= ~_BV(INT0);
}

uint16_t ATMega328P::timer1Value() {
    return TCNT1;
}
