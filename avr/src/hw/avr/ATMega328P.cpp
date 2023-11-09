//
// Created by ghisi on 09.11.22.
//

#include <avr/interrupt.h>
#include "ATMega328P.h"
#include "vector"

USARTInterruptHandler *ATMega328P::interruptHandler = nullptr;
Timer0InterruptHandler *ATMega328P::timer0InterruptHandler = nullptr;
TimerCompareMatchInterruptHandler *ATMega328P::timer1CompareMatchAInterruptHandler = nullptr;
TimerCompareMatchInterruptHandler *ATMega328P::timer1CompareMatchBInterruptHandler = nullptr;
ExternalInterruptHandler *ATMega328P::externalInterruptHandler = nullptr;

ATMega328P::ATMega328P() {
    UCSR0C = (_BV(UCSZ01)) | (_BV(UCSZ00));
//    UBRR0 = 25; //38k
    UBRR0 = 0; //1mbps
    //PD0 = RX
    //PD1 = TX
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
    OCR0A = 249;
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
    TCCR1B |= _BV(CS11); //CLK/8 //| _BV(CS10); //Clock with CLK/64 prescaler
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

void ATMega328P::resetTimer1() {
    TCNT1 = 0;
}

void ATMega328P::timer1ForceCompareMatchA() {
    TCCR1C |= _BV(FOC1A);
}

void ATMega328P::disableReceiver() {
    UCSR0B &= ~(_BV(RXEN0)); // | _BV(RXCIE0));
}

void ATMega328P::enableReceiver() {
    UCSR0B |= _BV(RXEN0); // | _BV(RXCIE0);
}

void ATMega328P::setInterruptHandler(USARTInterruptHandler *handler) {
    ATMega328P::interruptHandler = handler;
}

void ATMega328P::send(uint8_t byte) {
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = byte;
}

void ATMega328P::disableReadyToSendInterrupt() {
    UCSR0B &= ~_BV(UDRIE0);
}

void ATMega328P::disableTransmitter() {
    UCSR0B &= ~((_BV(TXEN0) | _BV(TXCIE0)));
//    DDRD &= ~(_BV(PORTD3) | _BV(PORTD2));
//    PORTD &= ~(_BV(PORTD3) | _BV(PORTD2));
}

void ATMega328P::enableTransmitterAndReadyToSendInterrupt() {
    UCSR0B |= _BV(TXEN0);// | _BV(UDRIE0); //| _BV(TXCIE0);
}

void USART_TX_vect(void) {
    if (ATMega328P::interruptHandler != nullptr) {
        ATMega328P::interruptHandler->transmissionFinished();
    }
}
void USART_RX_vect(void) {
    if (ATMega328P::interruptHandler != nullptr) {
        uint8_t byte = UDR0;
        ATMega328P::interruptHandler->frameReceived(byte);
    }
}

void USART_UDRE_vect(void) {
    if (ATMega328P::interruptHandler != nullptr) {
        ATMega328P::interruptHandler->readyToSend();
    }
}

char *ATMega328P::readLine() {
    enableReceiver();
    auto line = new char[10];
    for (uint8_t i = 0; i < 10; i++) {
        line[i] = 0;
    }
    char c = 0;
    for (uint8_t i = 0; i < 10; i++) {
        if (c == '\n') {
            break;
        }
        while (!(UCSR0A & (1<<RXC0)));
        c = UDR0;
        line[i] = c;
    }
    disableReceiver();

    return line;
}
