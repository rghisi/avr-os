//
// Created by ghisi on 27.10.22.
//

#ifndef AVR_ASYNCFUNCTION_H
#define AVR_ASYNCFUNCTION_H


#include <cstdint>
#include "functional"
#include "memory"
#include "Task.h"

class AsyncFunction: public Task {
public:
    explicit AsyncFunction(std::function<void(void)> lambda);
    ~AsyncFunction() override;
    void run() override;
    Type type() override;
    uint32_t delay() override;

private:
    std::function<void(void)> lambda;
};


#endif //AVR_ASYNCFUNCTION_H
