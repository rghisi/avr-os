//
// Created by ghisi on 17.09.22.
//

#include "WallClock.h"

void WallClock::processTick() {
    millis++;
}

uint32_t WallClock::now() const {
    return millis;
}
