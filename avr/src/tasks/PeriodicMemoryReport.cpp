//
// Created by ghisi on 27.10.22.
//

#include "PeriodicMemoryReport.h"
#include "../lcd/DrawText.h"
#include "cstdio"
#include "MemoryReport.h"

PeriodicMemoryReport::PeriodicMemoryReport(Messaging *eventDispatcher) {
    this->eventDispatcher = eventDispatcher;
}

PeriodicMemoryReport::~PeriodicMemoryReport() {
    eventDispatcher = nullptr;
}

void PeriodicMemoryReport::run() {
    extern int __heap_start, *__brkval;
    int v;
    uint16_t value = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
    eventDispatcher->send(new MemoryReport(value));
}

uint32_t PeriodicMemoryReport::delay() {
    return 1000;
}

Task::Type PeriodicMemoryReport::type() {
    return Type::PERIODIC;
}
