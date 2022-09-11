//
// Created by ghisi on 05.09.22.
//

#include "ATMega32U4.h"

USARTInterruptHandler *ATMega32U4::interruptHandler = nullptr;

ATMega32U4::ATMega32U4(ATMega32U4::BitRate bitRate) {
    switch (bitRate) {
        case BitRate::B9600:
            UBRR1 = 0x067;
            UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
            break;
    }
}

inline void ATMega32U4::disableReadyToSendInterrupt() {
    UCSR1B &= ~(1 << UDRIE1);
}

inline void ATMega32U4::disableTransmitter() {
    UCSR1B &= ~(1 << TXEN1);
}

inline void ATMega32U4::enableTransmitterAndReadyToSendInterrupt() {
    UCSR1B |= (1 << TXEN1) | (1 << UDRIE1);
}

void USART1_TX_vect(void) {
    if (ATMega32U4::interruptHandler != nullptr) {
        ATMega32U4::interruptHandler->transmissionFinished();
    }
}
void USART1_RX_vect(void) {
    if (ATMega32U4::interruptHandler != nullptr) {
        uint8_t byte = UDR1;
        ATMega32U4::interruptHandler->dataReceived(byte);
    }
}

void USART1_UDRE_vect(void) {
    if (ATMega32U4::interruptHandler != nullptr) {
        ATMega32U4::interruptHandler->readyToSend();
    }
}

void ATMega32U4::setInterruptHandler(USARTInterruptHandler *handler) {
    ATMega32U4::interruptHandler = handler;
}

inline void ATMega32U4::send(uint8_t byte) {
    UDR1 = byte;
}

inline void ATMega32U4::disableReceiver() {
    UCSR1B &= ~((1 << RXEN1) | (1 << RXCIE1));
}

inline void ATMega32U4::enableReceiver() {
    UCSR1B |= (1 << RXEN1) | (1 << RXCIE1);
}

