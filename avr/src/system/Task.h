//
// Created by ghisi on 13.10.22.
//

#ifndef AVR_TASK_H
#define AVR_TASK_H

#include <cstdint>
#include "Promise.h"
#include "Stack.h"

enum class TaskState: uint_fast8_t {
    CREATED, WAITING, RUNNING, BLOCKED, TERMINATED
};

class Task {
public:
    explicit Task(Stack *stack);
    ~Task();
    virtual void run() = 0;
    volatile uint32_t nextExecution = 0;
    bool operator<(const Task &rhs) const;
    bool operator>(const Task &rhs) const;
    bool operator<=(const Task &rhs) const;
    bool operator>=(const Task &rhs) const;

    TaskState state = TaskState::CREATED;
    Stack *stack;
protected:
    virtual void yield() final;
    virtual void sleep(uint16_t ms) final;
    virtual Promise * await(Promise*) final;
};

#endif //AVR_TASK_H
