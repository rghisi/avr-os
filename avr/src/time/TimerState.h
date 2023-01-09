//
// Created by ghisi on 1/3/23.
//

#ifndef AVR_TIMERSTATE_H
#define AVR_TIMERSTATE_H


#include "../system/Message.h"
#include "Timer.h"

class TimerState: public Message {
public:
    TimerState(int8_t minutes, int8_t seconds, Timer::State state);
    ~TimerState() override;
    int8_t minutes;
    int8_t seconds;
    Timer::State state;
};


#endif //AVR_TIMERSTATE_H
