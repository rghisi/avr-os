//
// Created by ghisi on 12.11.23.
//

#ifndef AVR_HEAPSTACK_H
#define AVR_HEAPSTACK_H

#include "cstddef"
#include "cstdint"
#include "Stack.h"

class HeapStack: public Stack {
public:
    explicit HeapStack(size_t stackSize) {
        stack = new uintptr_t[stackSize];
        pointer = reinterpret_cast<volatile uintptr_t>(&stack[stackSize - 1]);
    }

    ~HeapStack() override {
        delete[] stack;
    }
private:
    uintptr_t *stack;
};

#endif //AVR_HEAPSTACK_H
