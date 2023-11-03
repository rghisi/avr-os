//
// Created by ghisi on 11.03.23.
//

#ifndef AVR_OS_H
#define AVR_OS_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Messaging.h"
#include "TaskScheduler.h"
#include "MemoryAllocator.cpp"



class OS {
public:
    static TaskScheduler *scheduler;
    static Messaging *messaging;
    static MemoryAllocator<256> *memoryAllocator;
    static volatile uintptr_t stackPointer;

    static void send(Message* event);
    static void run();
    __attribute__ ((naked)) static void startTask(Task *task);
    __attribute__ ((naked)) static void switchToTask(Task *task);
    __attribute__ ((naked)) static void yield(Task*);
    static void *memalloc(size_t size);
    static void memfree(void *ptr);
    static uint16_t usedMemory();
};

#endif //AVR_OS_H
