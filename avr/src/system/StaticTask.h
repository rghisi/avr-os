//
// Created by ghisi on 05.11.23.
//

#ifndef AVR_STATICTASK_H
#define AVR_STATICTASK_H

#include "cstddef"
#include "Task.h"

template <size_t S>
class StaticTask: public Task {
protected:
    StaticTask() {
        stackPointer = reinterpret_cast<volatile uintptr_t>(&stack[S - 1]);
    }

private:
    volatile uint8_t *stack[S] = {nullptr};
};

#endif //AVR_STATICTASK_H
