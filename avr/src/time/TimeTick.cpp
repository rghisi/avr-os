//
// Created by ghisi on 12/30/22.
//

#include "TimeTick.h"
#include "TimeTickData.h"

TimeTick::TimeTick(EventDispatcher *eventDispatcher, WallClock *wallClock) {
    this->eventDispatcher = eventDispatcher;
    this->wallClock = wallClock;
}

void TimeTick::run() {
    auto now = wallClock->now();
    auto event = std::make_unique<Event>(
            Event(EventType::TIME_TICK, new TimeTickData(now))
            );
    eventDispatcher->dispatch(std::move(event));
}

uint32_t TimeTick::delay() {
    return 1000;
}

Task::Type TimeTick::type() {
    return Type::PERIODIC;
}
