//
// Created by ghisi on 13.10.22.
//

#ifndef AVR_TASK_H
#define AVR_TASK_H

#include <cstdint>

class Task {
public:
    enum class Type: uint8_t {
        PERIODIC,
        SINGLE,
        WAIT
    };
    virtual ~Task() = default;
    virtual void run() = 0;
    virtual uint32_t delay() = 0;
    virtual Type type() = 0;
    uint32_t nextExecution = 0;
    bool operator<(const Task &rhs) const {
        return nextExecution < rhs.nextExecution;
    }

    bool operator<=(const Task &rhs) const {
        return !(rhs < *this);
    }
};



#endif //AVR_TASK_H
