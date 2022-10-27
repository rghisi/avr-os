//
// Created by ghisi on 26.10.22.
//

#include "AsyncChain.h"
#include "AsyncWait.h"
#include "AsyncFunction.h"

AsyncChain *AsyncChain::then(std::function<void(void)> thenLambda) {
    auto async = std::make_unique<AsyncFunction>(std::move(thenLambda));
    chain.push_back(std::move(async));

    return this;
}

AsyncChain *AsyncChain::wait(uint16_t milliseconds) {
    auto asyncWait = std::make_unique<AsyncWait>(milliseconds);
    chain.push_back(std::move(asyncWait));

    return this;
}

std::unique_ptr<Async> AsyncChain::next() {
    if (!chain.empty()) {
        auto next = std::move(chain.front());
        chain.pop_front();
        return next;
    } else {
        return nullptr;
    }
}

bool AsyncChain::hasNext() {
    return !chain.empty();
}

AsyncChain::~AsyncChain() = default;
