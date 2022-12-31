//
// Created by ghisi on 12/30/22.
//

#include "TimeTicker.h"
#include "TimeTick.h"

TimeTicker::TimeTicker(EventDispatcher *eventDispatcher, WallClock *wallClock) {
    this->eventDispatcher = eventDispatcher;
    this->wallClock = wallClock;
}

void TimeTicker::run() {
    auto now = wallClock->now();
    auto event = new TimeTick(now);
    eventDispatcher->dispatch(event);
}

uint32_t TimeTicker::delay() {
    return 1000;
}

Task::Type TimeTicker::type() {
    return Type::PERIODIC;
}
