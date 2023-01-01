//
// Created by ghisi on 12/31/22.
//

#include "TaskSchedulingRequested.h"

TaskSchedulingRequested::TaskSchedulingRequested(Task *task): Message(MessageType::ASYNC_SCHEDULED) {
    this->task = task;
}

TaskSchedulingRequested::~TaskSchedulingRequested() {
    delete task;
}
