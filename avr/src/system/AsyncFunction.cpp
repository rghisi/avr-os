//
// Created by ghisi on 27.10.22.
//

#include "AsyncFunction.h"

AsyncFunction::AsyncFunction(std::function<void(void)> lambda) {
    this->lambda = std::move(lambda);
}

Async::Type AsyncFunction::type() {
    return Async::Type::IMMEDIATE;
}

void AsyncFunction::execute() {
    lambda();
}

uint32_t AsyncFunction::delay() {
    return 0;
}

AsyncFunction::~AsyncFunction() = default;