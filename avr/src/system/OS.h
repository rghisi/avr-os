//
// Created by ghisi on 11.03.23.
//

#ifndef AVR_OS_H
#define AVR_OS_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "TaskScheduler.h"
#include "MemoryAllocator.cpp"
#include "ContextSwitcher.h"
#include "Event.h"

class OS {
public:
    static TaskScheduler *scheduler;
    static MemoryAllocator<1280> *memoryAllocator;
    static ContextSwitcher *contextSwitcher;

    static void start();
    static void schedule(Task *task);
    static void schedule(PeriodicTask *task);
//    static Promise *execAsync(Task *task);
    static void startTask(Task *task);
    static void switchToTask(Task *task);
//    static void yield(Task*);
    static void yield();
    static Promise* await(Promise *promise);
    static void sleep(uint_fast16_t ms);
    static void *memalloc(size_t size);
    static void memfree(void *ptr);
    static Task* createTask(int_fast8_t (*entryPoint)(char *), char *args);
    static MemoryStats *memoryStats();

    static void dispatch(Event *event);
private:
    static Task* currentTask;
};


#endif //AVR_OS_H
