//
// Created by ghisi on 20.11.22.
//

#ifndef AVR_TIMER1_H
#define AVR_TIMER1_H
#include "cstdint"
class TimerCompareMatchInterruptHandler {
public:
    virtual void handleTimerCompareMatchInterrupt() = 0;
};

class Timer1 {
public:
    virtual void setupTimer1() = 0;
    virtual void startTimer1() = 0;
    virtual void stopTimer1() = 0;
    virtual uint16_t timer1Value() = 0;
    virtual void timer1CompareMatchA(uint16_t value) = 0;
    virtual void timer1CompareMatchB(uint16_t value) = 0;
    virtual void setTimer1CompareMatchAInterruptHandler(TimerCompareMatchInterruptHandler *handler) = 0;
    virtual void setTimer1CompareMatchBInterruptHandler(TimerCompareMatchInterruptHandler *handler) = 0;
    virtual void timer1DoNothingOnCompareMatchA() = 0;
    virtual void timer1ClearOnCompareMatchA() = 0;
    virtual void timer1SetOnCompareMatchA() = 0;
};

#endif //AVR_TIMER1_H
