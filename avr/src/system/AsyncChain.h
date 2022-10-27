//
// Created by ghisi on 26.10.22.
//

#ifndef AVR_ASYNCCHAIN_H
#define AVR_ASYNCCHAIN_H


#include "Async.h"
#include "list"

class AsyncChain {
public:
    ~AsyncChain();
    AsyncChain* then(std::function<void(void)> thenLambda);
    AsyncChain* wait(uint16_t milliseconds);
    std::unique_ptr<Async> next();
    bool hasNext();
private:
    std::list<std::unique_ptr<Async>> chain;
};


#endif //AVR_ASYNCCHAIN_H
