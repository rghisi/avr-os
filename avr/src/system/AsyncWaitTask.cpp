//
// Created by ghisi on 27.10.22.
//

#include "AsyncWaitTask.h"

AsyncWaitTask::AsyncWaitTask(uint32_t delay, EventDispatcher *eventDispatcher, std::unique_ptr<Event> callbackEvent) {
    this->milliseconds = delay;
    this->eventDispatcher = eventDispatcher;
    this->callbackEvent = std::move(callbackEvent);
}

void AsyncWaitTask::run() {
    eventDispatcher->dispatch(std::move(callbackEvent));
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
