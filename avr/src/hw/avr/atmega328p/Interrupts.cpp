//
// Created by ghisi on 15.11.23.
//

#include "../../../system/Interrupts.h"
#include <avr/interrupt.h>

inline void Interrupts::enable() {
    sei();
}

inline void Interrupts::disable() {
    cli();
}