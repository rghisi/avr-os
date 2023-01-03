//
// Created by ghisi on 1/2/23.
//

#include "Timer.h"
#include "TimerState.h"

Timer::Timer(Messaging *messaging,WallClock *wallClock) {
    this->messaging = messaging;
    this->wallClock = wallClock;
}

void Timer::handle(Message *event) {
    auto timeTick = static_cast<TimeTick*>(event);
    switch (state) {
        case State::WAITING_START:
            previousTimestamp = wallClock->now();
            milliseconds = 0;
            state = State::RUNNING;
            break;
        case State::RUNNING:
            milliseconds += timeTick->millis() - previousTimestamp;
            if (milliseconds >= 1000) {
                milliseconds -= 1000;
                seconds--;
            }
            if (seconds < 0) {
                seconds += 60;
                minutes--;
            }
            if (minutes < 0) {
                finish();
            }
            messaging->send(new TimerState(minutes, seconds, state));
            break;
        default:
            break;
    }
}

void Timer::stop() {
    state = State::STOPPED;
}

void Timer::start(uint8_t minutes, uint8_t seconds) {
    milliseconds = 0;
    this->seconds = seconds;
    this->minutes = minutes;
    state = State::WAITING_START;
}

void Timer::finish() {
    state = State::FINISHED;
}

void Timer::pause() {
    if (state == State::RUNNING || state == State::WAITING_START) {
        state = State::PAUSED;
    }
}

void Timer::resume() {
    if (state == State::PAUSED) {
        state = State::WAITING_START;
    }
}
