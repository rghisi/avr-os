//
// Created by ghisi on 27.10.22.
//

#include "PeriodicMemoryReport.h"

PeriodicMemoryReport::PeriodicMemoryReport(EventDispatcher *eventDispatcher) {
    this->eventDispatcher = eventDispatcher;
}

PeriodicMemoryReport::~PeriodicMemoryReport() {
    eventDispatcher = nullptr;
}

void PeriodicMemoryReport::run() {
    extern int __heap_start, *__brkval;
    int v;
    auto value = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
    auto event = new MemoryStats(value);
    eventDispatcher->dispatch(event);
}

uint32_t PeriodicMemoryReport::delay() {
    return 100;
}

Task::Type PeriodicMemoryReport::type() {
    return Type::PERIODIC;
}
