//
// Created by ghisi on 19.10.22.
//

#ifndef AVR_ASYNC_H
#define AVR_ASYNC_H


#include <cstdint>
#include "functional"
#include "memory"

class Async {
public:
    enum class Type {
        IMMEDIATE,
        WAIT
    };
    virtual ~Async() = default;
    virtual void execute() = 0;
    virtual Type type() = 0;
    virtual uint32_t delay() = 0;
};


#endif //AVR_ASYNC_H
