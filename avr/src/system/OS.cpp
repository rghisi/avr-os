//
// Created by ghisi on 18.03.23.
//


#include <avr/pgmspace.h>
#include "OS.h"
//#include "TaskExecPromise.h"
#include "../comms/Serial.h"
#include "cstring"
#include "cstdio"
#include "ExecutableTask.h"
#include "TimeWaitPromise.h"

Task* OS::currentTask = nullptr;

void OS::start() {
    Serial::send("\n\rStarting OS\n\r");
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

//kill this
//Promise *OS::execAsync(Task *task) {
//    scheduler->schedule(task);
//    return new TaskExecPromise(task);
//}

//scheduler
void OS::startTask(Task *task) {
    currentTask = task;
    contextSwitcher->startTask(task);
    currentTask = nullptr;
}

//scheduler
void OS::switchToTask(Task *task) {
    currentTask = task;
    contextSwitcher->switchToTask(task);
    currentTask = nullptr;
}

void OS::yield() {
    if (currentTask != nullptr) {
        currentTask->state = TaskState::WAITING;
        contextSwitcher->yield(currentTask);
    }
}

Promise* OS::await(Promise *promise) {
    if (!promise->isCompleted()) {
        currentTask->state = TaskState::BLOCKED;
        scheduler->add(currentTask, promise);
        contextSwitcher->yield(currentTask);
    }

    return promise;
}

void OS::sleep(uint_fast16_t ms) {
    auto asyncSleep = await(new TimeWaitPromise(ms));
    delete asyncSleep;
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

void OS::dispatch(Event *event) {

}

Task *OS::createTask(int_fast8_t (*entryPoint)(char *), char *args) {
    //switch context or allocator, then...
    auto* task = new ExecutableTask(entryPoint, args);
    return task;
}
