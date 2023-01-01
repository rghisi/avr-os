//
// Created by ghisi on 27.10.22.
//

#include "PeriodicMemoryReport.h"
#include "../lcd/DrawText.h"
#include "cstdio"
#include "../lcd/DisplayCommand.h"

PeriodicMemoryReport::PeriodicMemoryReport(MessageDispatcher *eventDispatcher) {
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
    sprintf(s, "%" PRIu16, value);
    auto event = DisplayCommand::drawText(0, 0, s);
    eventDispatcher->dispatch(event);
}

uint32_t PeriodicMemoryReport::delay() {
    return 200;
}

Task::Type PeriodicMemoryReport::type() {
    return Type::PERIODIC;
}
