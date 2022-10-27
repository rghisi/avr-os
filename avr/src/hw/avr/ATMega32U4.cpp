//
// Created by ghisi on 05.09.22.
//

#include "ATMega32U4.h"

#include <util/delay.h>

USARTInterruptHandler *ATMega32U4::interruptHandler = nullptr;
Timer0InterruptHandler *ATMega32U4::timer0InterruptHandler = nullptr;

ATMega32U4::ATMega32U4(ATMega32U4::BitRate bitRate) {
    switch (bitRate) {
        case BitRate::B9600:
            UBRR1 = 0x067;
            UCSR1C = (_BV(UCSZ11)) | (_BV(UCSZ10));
            break;
    }
    DDRD &= ~(_BV(PORTD3) | _BV(PORTD2));
    PORTD &= ~(_BV(PORTD3) | _BV(PORTD2));

    DDRB |= rxLed;
    DDRD |= txLed;
    rxLedOff();
    txLedOff();

    TCCR0A = _BV(WGM01);
    TCCR0B = _BV(CS01) | _BV(CS00);
    TIMSK0 = _BV(OCIE0A);
    TCNT0 = 0;
    OCR0A = 250;
}

inline void ATMega32U4::disableReadyToSendInterrupt() {
    UCSR1B &= ~_BV(UDRIE1);
}

inline void ATMega32U4::disableTransmitter() {
    UCSR1B &= ~((_BV(TXEN1) | _BV(TXCIE1)));
    DDRD &= ~(_BV(PORTD3) | _BV(PORTD2));
    PORTD &= ~(_BV(PORTD3) | _BV(PORTD2));
    txLedOff();
}

inline void ATMega32U4::enableTransmitterAndReadyToSendInterrupt() {
    UCSR1B |= _BV(TXEN1) | _BV(UDRIE1) | _BV(TXCIE1);
    txLedOn();
}

void USART1_TX_vect(void) {
    ATMega32U4::txLedOn();
    if (ATMega32U4::interruptHandler != nullptr) {
        ATMega32U4::interruptHandler->transmissionFinished();
    }
}
void USART1_RX_vect(void) {
    ATMega32U4::rxLedOn();
    if (ATMega32U4::interruptHandler != nullptr) {
        uint8_t byte = UDR1;
        ATMega32U4::interruptHandler->frameReceived(byte);
    }
    ATMega32U4::rxLedOff();
}

void USART1_UDRE_vect(void) {
    if (ATMega32U4::interruptHandler != nullptr) {
        ATMega32U4::interruptHandler->readyToSend();
    }
}

void TIMER0_COMPA_vect(void) {
    if (ATMega32U4::timer0InterruptHandler != nullptr) {
        ATMega32U4::timer0InterruptHandler->processTick();
    }
}

void ATMega32U4::setInterruptHandler(USARTInterruptHandler *handler) {
    ATMega32U4::interruptHandler = handler;
}

void ATMega32U4::setTimer0InterruptHandler(Timer0InterruptHandler *handler) {
    ATMega32U4::timer0InterruptHandler = handler;
}

inline void ATMega32U4::send(uint8_t byte) {
    txLedOff();
    UDR1 = byte;
}

inline void ATMega32U4::disableReceiver() {
    UCSR1B &= ~(_BV(RXEN1) | _BV(RXCIE1));
}

inline void ATMega32U4::enableReceiver() {
    UCSR1B |= _BV(RXEN1) | _BV(RXCIE1);
}

inline void ATMega32U4::txLedOff() {
    PORTD |= txLed;
}

inline void ATMega32U4::txLedOn() {
    PORTD &= ~txLed;
}

inline void ATMega32U4::rxLedOff() {
    PORTB |= rxLed;
}

inline void ATMega32U4::rxLedOn() {
    PORTB &= ~rxLed;
}



