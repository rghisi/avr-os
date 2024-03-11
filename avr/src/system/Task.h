//
// Created by ghisi on 13.10.22.
//

#ifndef AVR_TASK_H
#define AVR_TASK_H

#include <cstdint>
#include "Stack.h"
#include "StaticStack.h"

enum class TaskState: uint_fast8_t {
    CREATED, WAITING, RUNNING, BLOCKED, TERMINATED
};

class Task {
public:
    explicit Task();
    virtual ~Task();
    virtual void execute() = 0;

    TaskState state = TaskState::CREATED;
    Stack *stack;
//    MemoryAllocator<128> *memoryAllocator;
};

#endif //AVR_TASK_H
