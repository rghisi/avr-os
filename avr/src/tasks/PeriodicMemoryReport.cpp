//
// Created by ghisi on 27.10.22.
//

#include "PeriodicMemoryReport.h"

PeriodicMemoryReport::PeriodicMemoryReport(WallClock *wallClock, EventDispatcher *eventDispatcher) {
    this->wallClock = wallClock;
    this->eventDispatcher = eventDispatcher;
    this->memoryStats = MemoryStats();
}

PeriodicMemoryReport::~PeriodicMemoryReport() {
    eventDispatcher = nullptr;
}

void PeriodicMemoryReport::run() {
    extern int __heap_start, *__brkval;
    int v;
    memoryStats.value = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
    auto event = std::make_unique<Event>(Event(EventType::MEMORY_STATS_DISPATCHED, &memoryStats));
    eventDispatcher->dispatch(std::move(event));
}

uint32_t PeriodicMemoryReport::delay() {
    return 100;
}

Task::Type PeriodicMemoryReport::type() {
    return Type::PERIODIC;
}
