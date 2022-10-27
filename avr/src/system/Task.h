//
// Created by ghisi on 13.10.22.
//

#ifndef AVR_TASK_H
#define AVR_TASK_H

#include <cstdint>

class Task {
public:
    enum class Type {
        SINGLE,
        PERIODIC
    };
    virtual ~Task() = default;
    virtual void run() = 0;
    virtual uint32_t delay() = 0;
    virtual Type type() = 0;
};



#endif //AVR_TASK_H
