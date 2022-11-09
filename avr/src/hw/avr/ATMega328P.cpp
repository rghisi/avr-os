//
// Created by ghisi on 09.11.22.
//

#include <avr/interrupt.h>
#include "ATMega328P.h"

void ATMega328P::setTimer0InterruptHandler(Timer0InterruptHandler *handler) {

}

void ATMega328P::disableReadyToSendInterrupt() {

}

void ATMega328P::disableTransmitter() {

}

void ATMega328P::enableTransmitterAndReadyToSendInterrupt() {

}

void ATMega328P::enableReceiver() {

}

void ATMega328P::disableReceiver() {

}

void ATMega328P::setInterruptHandler(USARTInterruptHandler *handler) {

}

void ATMega328P::send(uint8_t byte) {

}

void ATMega328P::enableInterrupts() {
    sei();
}

void ATMega328P::disableInterrupts() {
    cli();
}
