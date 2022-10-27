//
// Created by ghisi on 24.10.22.
//

#ifndef AVR_ASYNCWAIT_H
#define AVR_ASYNCWAIT_H


#include "Async.h"

class AsyncWait: public Async {
public:
    explicit AsyncWait(uint32_t milliseconds);
    ~AsyncWait() override;
    void execute() override;
    Type type() override;
    uint32_t delay() override;

private:
    uint32_t milliseconds;
};


#endif //AVR_ASYNCWAIT_H
