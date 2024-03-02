//
// Created by ghisi on 12.03.23.
//
#include "system/Task.h"
#include "system/OS.h"
#include "system/TimeWaitPromise.h"

Task::Task(Stack *stack) {
    this->stack = stack;
}

Task::~Task() {
    delete stack;
}

void Task::yield() {
    state = TaskState::WAITING;
    OS::yield(this);
}

void Task::sleep(uint16_t ms) {
    auto a = await(new TimeWaitPromise(ms));
    delete a;
}

Promise *Task::await(Promise *promise) {
    if (!promise->isCompleted()) {
        state = TaskState::BLOCKED;
        OS::await(this, promise);
    }

    return promise;
}
