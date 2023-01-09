//
// Created by ghisi on 27.10.22.
//

#include "PeriodicMemoryReport.h"
#include "../lcd/DrawText.h"
#include "cstdio"

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
    auto s = new char[5];
    sprintf(s, "%04" PRIu16, value);
    auto event = new DrawText(12, 1, s);
    eventDispatcher->send(event);
}

uint32_t PeriodicMemoryReport::delay() {
    return 200;
}

Task::Type PeriodicMemoryReport::type() {
    return Type::PERIODIC;
}
