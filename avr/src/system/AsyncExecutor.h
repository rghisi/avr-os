//;
// Created by ghisi on 20.10.22.
//

#ifndef AVR_ASYNCEXECUTOR_H
#define AVR_ASYNCEXECUTOR_H


#include "EventHandler.h"
#include "MessageDispatcher.h"
#include "TaskScheduler.h"
#include "AsyncChain.h"

class AsyncExecutor: public EventHandler {
public:
    explicit AsyncExecutor(TaskScheduler *taskScheduler, MessageDispatcher *eventDispatcher);
    bool handle(Message* event) override;

private:
    TaskScheduler *taskScheduler;
    MessageDispatcher *eventDispatcher;
    void executeAsync(Message* event);
    void executeChain(Message* event);
    static constexpr MessageType messageTypes[] = {ASYNC_SCHEDULED, ASYNC_CHAIN_SCHEDULED};
    static constexpr uint8_t messageTypeCount = 2;
};


#endif //AVR_ASYNCEXECUTOR_H
