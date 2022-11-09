//
// Created by ghisi on 26.10.22.
//

#include "AsyncChain.h"
#include "AsyncFunction.h"
#include "Event.h"
#include "AsyncWaitTask.h"

AsyncChain::AsyncChain(EventDispatcher *eventDispatcher) {
    this->eventDispatcher = eventDispatcher;
};

AsyncChain::~AsyncChain() = default;

AsyncChain *AsyncChain::then(std::function<void(void)> thenLambda) {
    auto async = std::make_unique<AsyncFunction>(std::move(thenLambda));
    chain.push_back(std::move(async));

    return this;
}

AsyncChain *AsyncChain::wait(uint16_t milliseconds) {
    auto callbackEvent = std::make_unique<Event>(Event(ASYNC_CHAIN_SCHEDULED, this));
    auto asyncWait = std::make_unique<AsyncWaitTask>(milliseconds, eventDispatcher, std::move(callbackEvent));
    chain.push_back(std::move(asyncWait));

    return this;
}

std::unique_ptr<Task> AsyncChain::next() {
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

void AsyncChain::schedule() {
    auto event = std::make_unique<Event>(Event(ASYNC_CHAIN_SCHEDULED, this));
    eventDispatcher->dispatch(std::move(event));
}
