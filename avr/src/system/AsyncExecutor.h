//;
// Created by ghisi on 20.10.22.
//

#ifndef AVR_ASYNCEXECUTOR_H
#define AVR_ASYNCEXECUTOR_H


#include "EventHandler.h"
#include "EventDispatcher.h"
#include "TaskScheduler.h"
#include "AsyncChain.h"

class AsyncExecutor: public EventHandler {
public:
    explicit AsyncExecutor(TaskScheduler *taskScheduler, EventDispatcher *eventDispatcher);
    EventType eventType() override;
    bool handle(std::unique_ptr<Event> event) override;

private:
    TaskScheduler *taskScheduler;
    EventDispatcher *eventDispatcher;
    void executeAsync(std::unique_ptr<Event> event);
    void executeChain(std::unique_ptr<Event> event);
};


#endif //AVR_ASYNCEXECUTOR_H
