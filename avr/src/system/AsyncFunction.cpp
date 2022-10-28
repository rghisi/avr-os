//
// Created by ghisi on 27.10.22.
//

#include "AsyncFunction.h"

AsyncFunction::AsyncFunction(std::function<void(void)> lambda) {
    this->lambda = std::move(lambda);
}

Task::Type AsyncFunction::type() {
    return Task::Type::SINGLE;
}

void AsyncFunction::run() {
    lambda();
}

uint32_t AsyncFunction::delay() {
    return 0;
}

AsyncFunction::~AsyncFunction() = default;