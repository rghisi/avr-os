//
// Created by ghisi on 13.10.22.
//

#ifndef AVR_TASK_H
#define AVR_TASK_H

#include <cstdint>
#include "functional"
#include "Promise.h"

enum class TaskState: uint_fast8_t {
    CREATED, WAITING, RUNNING, BLOCKED, TERMINATED
};

class Task {
public:
    ~Task() = default;
    virtual void run() = 0;
    volatile uint32_t nextExecution = 0;
    bool operator<(const Task &rhs) const;
    bool operator>(const Task &rhs) const;
    bool operator<=(const Task &rhs) const;
    bool operator>=(const Task &rhs) const;

    volatile TaskState state = TaskState::CREATED;
    volatile uintptr_t stackPointer = 0;
protected:
    virtual void yield() final;
    virtual void sleep(uint16_t ms) final;
    virtual void await(Promise*) final;
private:
};

#endif //AVR_TASK_H
