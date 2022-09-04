//
// Created by ghisi on 05.09.22.
//

#include "ATMega32U4.h"
#include <avr/io.h>

inline void ATMega32U4::disableReadyToSendInterrupt() {
    UCSR1B &= ~(1 << UDRIE1);
}

inline void ATMega32U4::disableTransmitter() {
    UCSR1B &= ~(1 << TXEN1);
}

inline void ATMega32U4::enableTransmitterAndReadyToSendInterrupt() {
    UCSR1B |= (1 << TXEN1) | (1 << UDRIE1);
}
