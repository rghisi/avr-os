//
// Created by ghisi on 12/30/22.
//

#ifndef AVR_TIMETICKER_H
#define AVR_TIMETICKER_H


#include "../system/Task.h"
#include "../system/WallClock.h"
#include "../system/Messaging.h"

class TimeTicker: public Task {
public:
    explicit TimeTicker(Messaging *eventDispatcher, WallClock *wallClock);
    ~TimeTicker() override = default;
    void run() override;
    uint32_t delay() override;
    Type type() override;
private:
    Messaging *eventDispatcher;
    WallClock *wallClock;
};


#endif //AVR_TIMETICKER_H
