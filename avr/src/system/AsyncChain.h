//
// Created by ghisi on 26.10.22.
//

#ifndef AVR_ASYNCCHAIN_H
#define AVR_ASYNCCHAIN_H


#include "list"
#include "Task.h"
#include "memory"
#include "functional"
#include "MessageDispatcher.h"

class AsyncChain {
public:
    AsyncChain(MessageDispatcher *eventDispatcher);
    ~AsyncChain();
    AsyncChain* then(std::function<void(void)> thenLambda);
    AsyncChain* wait(uint16_t milliseconds);
    void schedule();
    std::unique_ptr<Task> next();
    bool hasNext();
private:
    MessageDispatcher *eventDispatcher;
    std::list<std::unique_ptr<Task>> chain;
};


#endif //AVR_ASYNCCHAIN_H
