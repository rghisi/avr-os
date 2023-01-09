//
// Created by ghisi on 26.10.22.
//

#include "AsyncChain.h"
#include "AsyncFunction.h"
#include "Message.h"
#include "AsyncWaitTask.h"
#include "AsyncChainSchedulingRequest.h"

AsyncChain::AsyncChain(Messaging *messaging) {
    this->eventDispatcher = messaging;
};

AsyncChain::~AsyncChain() = default;

AsyncChain *AsyncChain::then(std::function<void(void)> thenLambda) {
    auto async = std::make_unique<AsyncFunction>(std::move(thenLambda));
    chain.push_back(std::move(async));

    return this;
}

AsyncChain *AsyncChain::wait(uint16_t milliseconds) {
    auto callbackEvent = new AsyncChainSchedulingRequest(this);
    auto asyncWait = std::make_unique<AsyncWaitTask>(milliseconds, eventDispatcher, callbackEvent);
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
    auto event = new AsyncChainSchedulingRequest(this);
    eventDispatcher->send(event);
}

bool AsyncChain::isCancelled() {
    return cancelled;
}

void AsyncChain::cancel() {
    cancelled = true;
}
