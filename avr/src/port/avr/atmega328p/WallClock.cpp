//
// Created by ghisi on 17.09.22.
//

#include <avr/io.h>
#include "../../../system/WallClock.h"

extern "C" void TIMER0_COMPA_vect(void) __attribute__ ((signal));

volatile uint32_t WallClock::now = 0;

/**
 * Setting Timer0 to 1ms period and enabling compare interrup
 */
void WallClock::setup() {
    TCCR0A = _BV(WGM01);
    TCCR0B = _BV(CS01) | _BV(CS00);
    TCNT0 = 0;
    OCR0A = 249;
    TIMSK0 = _BV(OCIE0A);
    WallClock::now = 0;
}
extern "C" {
    void TIMER0_COMPA_vect(void) {
        WallClock::now = WallClock::now + 1;
    }
}