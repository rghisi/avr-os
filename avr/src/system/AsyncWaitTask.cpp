//
// Created by ghisi on 27.10.22.
//

#include "AsyncWaitTask.h"

AsyncWaitTask::AsyncWaitTask(uint32_t delay, MessageDispatcher *eventDispatcher, Message* callbackEvent) {
    this->milliseconds = delay;
    this->eventDispatcher = eventDispatcher;
    this->callbackEvent = callbackEvent;
}

void AsyncWaitTask::run() {
    eventDispatcher->dispatch(callbackEvent);
}

uint32_t AsyncWaitTask::delay() {
    return milliseconds;
}

Task::Type AsyncWaitTask::type() {
    return Type::WAIT;
}

AsyncWaitTask::~AsyncWaitTask() {
    eventDispatcher = nullptr;
    callbackEvent = nullptr;
}
