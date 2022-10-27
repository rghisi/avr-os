//
// Created by ghisi on 27.10.22.
//

#include "PeriodicMemoryReport.h"

PeriodicMemoryReport::PeriodicMemoryReport(EventDispatcher *eventDispatcher) {
    this->eventDispatcher = eventDispatcher;
    this->memoryStats = MemoryStats();
}

PeriodicMemoryReport::~PeriodicMemoryReport() {
    eventDispatcher = nullptr;
}

void PeriodicMemoryReport::run() {
    extern int __heap_start, *__brkval;
    auto a = (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
    memoryStats.value = a;
    eventDispatcher->dispatch(new Event(EventType::CPU_STATS_DISPATCHED, &memoryStats));
}

uint32_t PeriodicMemoryReport::delay() {
    return 500;
}

Task::Type PeriodicMemoryReport::type() {
    return Type::PERIODIC;
}
