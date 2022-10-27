//
// Created by ghisi on 17.09.22.
//

#ifndef AVR_WALLCLOCK_H
#define AVR_WALLCLOCK_H


#include "cstdint"
#include "../hw/Timer0.h"
#include "EventDispatcher.h"

class WallClock: public Timer0InterruptHandler {
public:
    void processTick() override;
    uint32_t now() const;

private:
    uint32_t millis = 0;
};


#endif //AVR_WALLCLOCK_H
