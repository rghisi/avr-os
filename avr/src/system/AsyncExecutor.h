//;
// Created by ghisi on 20.10.22.
//

#ifndef AVR_ASYNCEXECUTOR_H
#define AVR_ASYNCEXECUTOR_H


#include "Subscriber.h"
#include "Messaging.h"
#include "TaskScheduler.h"
#include "AsyncChain.h"

class AsyncExecutor: public Subscriber {
public:
    explicit AsyncExecutor(TaskScheduler *taskScheduler, Messaging *eventDispatcher);
    void handle(Message* event) override;

private:
    TaskScheduler *taskScheduler;
    Messaging *eventDispatcher;
    void executeAsync(Message* event);
    void executeChain(Message* event);
};


#endif //AVR_ASYNCEXECUTOR_H
