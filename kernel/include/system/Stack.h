//
// Created by ghisi on 12.11.23.
//

#ifndef AVR_STACK_H
#define AVR_STACK_H


#include "cstdint"

class Stack {
public:
    virtual ~Stack() = default;
    volatile uintptr_t pointer = 0;
};

#endif //AVR_STACK_H
