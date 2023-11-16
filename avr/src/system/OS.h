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

class OS {
public:
    static TaskScheduler *scheduler;
    static MemoryAllocator<1152> *memoryAllocator;
    static ContextSwitcher *contextSwitcher;

    static void start();
    static void schedule(Task *task);
    static void schedule(PeriodicTask *task);
    static Promise *execAsync(Task *task);
    static void startTask(Task *task);
    static void switchToTask(Task *task);
    static void yield(Task*);
    static void await(Task *task, Promise *promise);
    static void *memalloc(size_t size);
    static void memfree(void *ptr);
    static MemoryStats *memoryStats();
};

#endif //AVR_OS_H
