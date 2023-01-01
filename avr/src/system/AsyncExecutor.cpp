//
// Created by ghisi on 20.10.22.
//

#include "AsyncExecutor.h"
#include "AsyncChain.h"
#include "TaskSchedulingRequested.h"
#include "AsyncChainSchedulingRequest.h"

AsyncExecutor::AsyncExecutor(TaskScheduler *taskScheduler, MessageDispatcher *eventDispatcher) {
    this->taskScheduler = taskScheduler;
    this->eventDispatcher = eventDispatcher;
}

MessageType AsyncExecutor::eventType() {
    return ASYNC_SCHEDULED;
}

bool AsyncExecutor::handle(Message* event) {
    switch (event->type()) {
        case ASYNC_SCHEDULED:
            executeAsync(event);
            break;
        case ASYNC_CHAIN_SCHEDULED:
        default:
            executeChain(event);
            break;
    }
    return false;
}

void AsyncExecutor::executeAsync(Message* event) {
    auto *async = static_cast<TaskSchedulingRequested*>(event);
    async->task->run();
}

void AsyncExecutor::executeChain(Message* event) {
    auto *asyncChain = static_cast<AsyncChainSchedulingRequest*>(event)->asyncChain;
    if (asyncChain->hasNext()) {
        auto nextAsync = asyncChain->next();
        switch (nextAsync->type()) {
            case Task::Type::SINGLE:
                nextAsync->run();
                if (asyncChain->hasNext()) {
                    auto newEvent = new AsyncChainSchedulingRequest(asyncChain);
                    eventDispatcher->dispatch(newEvent);
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
