//
// Created by ghisi on 27.10.22.
//

#include "AsyncWaitTask.h"

AsyncWaitTask::AsyncWaitTask(uint32_t delay, EventDispatcher *eventDispatcher, AsyncChain *asyncChain) {
    this->milliseconds = delay;
    this->eventDispatcher = eventDispatcher;
    this->asyncChain = asyncChain;
}

void AsyncWaitTask::run() {
    eventDispatcher->dispatch(new Event(ASYNC_CHAIN_SCHEDULED, asyncChain));
}

uint32_t AsyncWaitTask::delay() {
    return milliseconds;
}

Task::Type AsyncWaitTask::type() {
    return Type::SINGLE;
}

AsyncWaitTask::~AsyncWaitTask() {
    eventDispatcher = nullptr;
    asyncChain = nullptr;
}
