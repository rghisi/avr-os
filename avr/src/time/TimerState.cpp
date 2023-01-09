//
// Created by ghisi on 1/3/23.
//

#include "TimerState.h"

TimerState::~TimerState() = default;

TimerState::TimerState(int8_t minutes, int8_t seconds, Timer::State state) : Message(MessageType::TIMER_STATE) {
    this->minutes = minutes;
    this->seconds = seconds;
    this->state = state;

}
