//
// Created by ghisi on 12/30/22.
//

#ifndef AVR_TIMETICK_H
#define AVR_TIMETICK_H


#include "../system/Task.h"
#include "../system/WallClock.h"

class TimeTick: public Task {
public:
    explicit TimeTick(EventDispatcher *eventDispatcher, WallClock *wallClock);
    ~TimeTick() override = default;
    void run() override;
    uint32_t delay() override;
    Type type() override;
private:
    EventDispatcher *eventDispatcher;
    WallClock *wallClock;
};


#endif //AVR_TIMETICK_H
