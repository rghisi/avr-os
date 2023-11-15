//
// Created by ghisi on 18.03.23.
//


#include <avr/pgmspace.h>
#include "OS.h"
#include "TaskExecPromise.h"
#include "../comms/Serial.h"
#include "cstring"
#include "cstdio"
#include "Interrupts.h"

#define saveContext() \
asm volatile ( \
        "push r0 \n\t"  \
        "in r0, __SREG__ \n\t"  \
        "cli \n\t"  \
        "push r0 \n\t"  \
        "push r1 \n\t"  \
        "clr r1 \n\t"   \
        "push r2 \n\t"  \
        "push r3 \n\t"  \
        "push r4 \n\t"  \
        "push r5 \n\t"  \
        "push r6 \n\t"  \
        "push r7 \n\t"  \
        "push r8 \n\t"  \
        "push r9 \n\t"  \
        "push r10 \n\t" \
        "push r11 \n\t" \
        "push r12 \n\t" \
        "push r13 \n\t" \
        "push r14 \n\t" \
        "push r15 \n\t" \
        "push r16 \n\t" \
        "push r17 \n\t" \
        "push r18 \n\t" \
        "push r19 \n\t" \
        "push r20 \n\t" \
        "push r21 \n\t" \
        "push r22 \n\t" \
        "push r23 \n\t" \
        "push r24 \n\t" \
        "push r25 \n\t" \
        "push r26 \n\t" \
        "push r27 \n\t" \
        "push r28 \n\t" \
        "push r29 \n\t" \
        "push r30 \n\t" \
        "push r31 \n\t" \
        )

#define restoreContext() \
    asm volatile (  \
        "pop r31 \n\t"  \
        "pop r30 \n\t"  \
        "pop r29 \n\t"  \
        "pop r28 \n\t"  \
        "pop r27 \n\t"  \
        "pop r26 \n\t"  \
        "pop r25 \n\t"  \
        "pop r24 \n\t"  \
        "pop r23 \n\t"  \
        "pop r22 \n\t"  \
        "pop r21 \n\t"  \
        "pop r20 \n\t"  \
        "pop r19 \n\t"  \
        "pop r18 \n\t"  \
        "pop r17 \n\t"  \
        "pop r16 \n\t"  \
        "pop r15 \n\t"  \
        "pop r14 \n\t"  \
        "pop r13 \n\t"  \
        "pop r12 \n\t"  \
        "pop r11 \n\t"  \
        "pop r10 \n\t"  \
        "pop r9 \n\t"   \
        "pop r8 \n\t"   \
        "pop r7 \n\t"   \
        "pop r6 \n\t"   \
        "pop r5 \n\t"   \
        "pop r4 \n\t"   \
        "pop r3 \n\t"   \
        "pop r2 \n\t"   \
        "pop r1 \n\t"   \
        "pop r0 \n\t"   \
        "out __SREG__, r0 \n\t" \
        "pop r0 \n\t"   \
        "sei     \n\t"  \
        "ret     \n\t"  \
        )


volatile uint16_t OS::stackPointer = 0;

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
    saveContext();
    OS::stackPointer = SP;
    SP = task->stack->pointer;
    sei();
    task->run();
    SP = OS::stackPointer;
    restoreContext();
}

void OS::switchToTask(Task *task) {
    saveContext();
    OS::stackPointer = SP;
    SP = task->stack->pointer;
    restoreContext();
}

void OS::yield(Task *task) {
    saveContext();
    task->stack->pointer = SP;
    SP = OS::stackPointer;
    restoreContext();
}

void OS::await(Task *task, Promise *promise) {
    scheduler->add(task, promise);
    yield(task);
}

void *OS::memalloc(size_t len) {
    return OS::memoryAllocator->allocate(len);
}

void OS::memfree(void *p) {
    OS::memoryAllocator->free(p);
}

MemoryStats *OS::memoryStats() {
    return OS::memoryAllocator->stats();
}