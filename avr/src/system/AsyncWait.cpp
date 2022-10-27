//
// Created by ghisi on 24.10.22.
//

#include "AsyncWait.h"

AsyncWait::AsyncWait(uint32_t milliseconds) {
    this->milliseconds = milliseconds;
}

Async::Type AsyncWait::type() {
    return Async::Type::WAIT;
}

void AsyncWait::execute() {
}

uint32_t AsyncWait::delay() {
    return milliseconds;
}

AsyncWait::~AsyncWait() = default;
