//
// Created by ghisi on 17.09.22.
//

#ifndef AVR_WALLCLOCK_H
#define AVR_WALLCLOCK_H

#include "cstdint"

class WallClock {
public:
    static void setup();
    static volatile uint32_t now;
private:
};

#endif //AVR_WALLCLOCK_H
