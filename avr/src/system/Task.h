//
// Created by ghisi on 13.10.22.
//

#ifndef AVR_TASK_H
#define AVR_TASK_H

#include <cstdint>
#include "functional"

enum class TaskState: uint8_t {
    CREATED, WAITING, RUNNING, BLOCKED, TERMINATED
};

class Task {
public:
    ~Task() = default;
    virtual void run() = 0;
    uint32_t nextExecution = 0;
    bool operator<(const Task &rhs) const;
    bool operator>(const Task &rhs) const;
    bool operator<=(const Task &rhs) const;
    bool operator>=(const Task &rhs) const;

    TaskState state = TaskState::CREATED;
    static constexpr size_t STACK_SIZE = 128;
    volatile uintptr_t stackPointer = reinterpret_cast<volatile uintptr_t>(&stack[STACK_SIZE - 1]);
protected:
    virtual void yield() final;
    virtual void sleep(uint16_t ms) final;
private:
    volatile uint8_t *stack[STACK_SIZE] = {nullptr};
};



#endif //AVR_TASK_H
