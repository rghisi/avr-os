//
// Created by ghisi on 1/2/23.
//

#ifndef AVR_TIMER_H
#define AVR_TIMER_H


#include "cstdint"
#include "../system/Subscriber.h"
#include "../system/WallClock.h"
#include "TimeTick.h"
#include "../system/Messaging.h"

class Timer: public Subscriber {
public:
    enum class State: uint8_t {
        STOPPED, WAITING_START, RUNNING, PAUSED, FINISHED
    };
    explicit Timer(Messaging *messaging, WallClock *wallClock);
    void start(uint8_t minutes, uint8_t seconds);
    void stop();
    void pause();
    void resume();
    void handle(Message *event) override;
private:
    State state = State::STOPPED;
    uint32_t previousTimestamp;
    uint16_t milliseconds;
    int8_t seconds;
    int8_t minutes;
    Messaging *messaging;
    WallClock *wallClock;
    void finish();
};


#endif //AVR_TIMER_H
