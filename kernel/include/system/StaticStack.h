//
// Created by ghisi on 12.11.23.
//

#ifndef AVR_STATICSTACK_H
#define AVR_STATICSTACK_H

#include "cstddef"
#include "Stack.h"

template <size_t S>
class StaticStack: public Stack {
public:
    StaticStack() {
        pointer = reinterpret_cast<volatile uintptr_t>(&stack[S - 1]);
    }
    ~StaticStack() override = default;
private:
    volatile uint8_t *stack[S]{};
};

#endif //AVR_STATICSTACK_H
