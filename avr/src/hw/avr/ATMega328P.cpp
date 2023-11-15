//
// Created by ghisi on 09.11.22.
//

#include <avr/interrupt.h>
#include "ATMega328P.h"
#include "vector"

USARTInterruptHandler *ATMega328P::interruptHandler = nullptr;

ATMega328P::ATMega328P() {
    UCSR0C = (_BV(UCSZ01)) | (_BV(UCSZ00));
//    UBRR0 = 25; //38k
    UBRR0 = 0; //1mbps
    //PD0 = RX
    //PD1 = TX
}

void ATMega328P::disableReceiver() {
    UCSR0B &= ~(_BV(RXEN0));
}

void ATMega328P::enableReceiver() {
    UCSR0B |= _BV(RXEN0);
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
}

void ATMega328P::enableTransmitter() {
    UCSR0B |= _BV(TXEN0);
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

void ATMega328P::readLine(PromiseWithReturn<char*> *promise) {
    auto line = new char[10];
    enableReceiver();

//    for (uint8_t i = 0; i < 10; i++) {
//        line[i] = 0;
//    }
//    char c = 0;
//    for (uint8_t i = 0; i < 10; i++) {
//        if (c == '\n') {
//            break;
//        }
//        while (!(UCSR0A & (1<<RXC0)));
//        c = UDR0;
//        line[i] = c;
//    }
//    disableReceiver();

    promise->data = line;
    promise->complete();
}
