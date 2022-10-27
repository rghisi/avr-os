//
// Created by ghisi on 27.10.22.
//

#ifndef AVR_ASYNCWAITTASK_H
#define AVR_ASYNCWAITTASK_H


#include "Task.h"
#include "cstdint"
#include "EventDispatcher.h"
#include "AsyncChain.h"

class AsyncWaitTask: public Task {
public:
    AsyncWaitTask(uint32_t delay, EventDispatcher *pDispatcher, AsyncChain *pChain);
    ~AsyncWaitTask() override;
    void run() override;
    uint32_t delay() override;
    Type type() override;
private:
    EventDispatcher *eventDispatcher;
    AsyncChain *asyncChain;
    uint32_t milliseconds;
};


#endif //AVR_ASYNCWAITTASK_H
