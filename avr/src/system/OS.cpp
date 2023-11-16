//
// Created by ghisi on 18.03.23.
//


#include <avr/pgmspace.h>
#include "OS.h"
#include "TaskExecPromise.h"
#include "../comms/Serial.h"
#include "cstring"
#include "cstdio"

void OS::start() {
    auto stringBuffer = new char[60];
    sprintf_P(stringBuffer, PSTR("\n\r\n\r--------------------- Starting ---------------------\n\r\n\r"));
    Serial::send(stringBuffer, strlen(stringBuffer));

    WallClock::setup();
    sei();
    scheduler->run();
}

void OS::schedule(Task *task) {
    scheduler->schedule(task);
}

void OS::schedule(PeriodicTask *task) {
    scheduler->schedule(task);
}

Promise *OS::execAsync(Task *task) {
    scheduler->schedule(task);
    return new TaskExecPromise(task);
}

void OS::startTask(Task *task) {
    contextSwitcher->startTask(task);
}

void OS::switchToTask(Task *task) {
    contextSwitcher->switchToTask(task);
}

void OS::yield(Task *task) {
    contextSwitcher->yield(task);
}

void OS::await(Task *task, Promise *promise) {
    scheduler->add(task, promise);
    yield(task);
}

void *OS::memalloc(size_t len) {
    return memoryAllocator->allocate(len);
}

void OS::memfree(void *p) {
    memoryAllocator->free(p);
}

MemoryStats *OS::memoryStats() {
    return memoryAllocator->stats();
}