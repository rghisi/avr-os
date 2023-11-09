//
// Created by ghisi on 08.11.23.
//

#ifndef AVR_HEAPTASK_H
#define AVR_HEAPTASK_H

#include "cstddef"
#include "Task.h"

class HeapTask: public Task {
protected:
    explicit HeapTask(size_t stackSize) {
        stack = new uintptr_t[stackSize];
        stackPointer = reinterpret_cast<volatile uintptr_t>(&stack[stackSize - 1]);
    }

    ~HeapTask() override {
        delete[] stack;
    }

private:
    uintptr_t *stack;
};

#endif //AVR_HEAPTASK_H
