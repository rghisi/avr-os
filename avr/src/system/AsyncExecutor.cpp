//
// Created by ghisi on 20.10.22.
//

#include "AsyncExecutor.h"
#include "AsyncChain.h"

AsyncExecutor::AsyncExecutor(TaskScheduler *taskScheduler, EventDispatcher *eventDispatcher) {
    this->taskScheduler = taskScheduler;
    this->eventDispatcher = eventDispatcher;
}

EventType AsyncExecutor::type() {
    return ASYNC_SCHEDULED;
}

bool AsyncExecutor::handle(Event *event) {
    switch (event->type()) {
        case ASYNC_SCHEDULED:
            executeAsync(event);
            break;
        case ASYNC_CHAIN_SCHEDULED:
        default:
            executeChain(event);
            break;
    }

    return true;
}

void AsyncExecutor::executeAsync(Event *event) {
    auto *async = static_cast<Task*>(event->data());
    async->run();
    delete async;
}

void AsyncExecutor::executeChain(Event *event) {
    auto *asyncChain = static_cast<AsyncChain*>(event->data());
    if (asyncChain->hasNext()) {
        auto nextAsync = asyncChain->next();
        switch (nextAsync->type()) {
            case Task::Type::SINGLE:
                nextAsync->run();
                if (asyncChain->hasNext()) {
                    eventDispatcher->dispatch(new Event(ASYNC_CHAIN_SCHEDULED, asyncChain));
                } else {
                    delete asyncChain;
                }
                break;
            case Task::Type::PERIODIC:
                break;
            case Task::Type::WAIT:
                taskScheduler->schedule(nextAsync.release());
                break;
        }
    } else {
        delete asyncChain;
    }
}