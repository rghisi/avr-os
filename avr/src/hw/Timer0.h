//
// Created by ghisi on 11.10.22.
//

#ifndef AVR_TIMER0_H
#define AVR_TIMER0_H

class Timer0InterruptHandler {
public:
    virtual void processTick() = 0;
};

class Timer0 {
public:
    virtual void setTimer0InterruptHandler(Timer0InterruptHandler *handler) = 0;
};

#endif //AVR_TIMER0_H
