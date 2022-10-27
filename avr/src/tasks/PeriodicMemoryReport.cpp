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
    memoryStats.value = wallClock->now();
    eventDispatcher->dispatch(new Event(EventType::MEMORY_STATS_DISPATCHED, &memoryStats));
}

uint32_t PeriodicMemoryReport::delay() {
    return 500;
}

Task::Type PeriodicMemoryReport::type() {
    return Type::PERIODIC;
}
