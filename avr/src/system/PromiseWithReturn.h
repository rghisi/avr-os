//
// Created by ghisi on 12.11.23.
//

#ifndef AVR_PROMISEWITHRETURN_H
#define AVR_PROMISEWITHRETURN_H


#include "Promise.h"

template <typename T>
class PromiseWithReturn: public Promise {
public:
    ~PromiseWithReturn() override {
        delete data;
    }
    T data;
    size_t size;
};
#endif //AVR_PROMISEWITHRETURN_H
