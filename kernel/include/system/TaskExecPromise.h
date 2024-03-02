//
// Created by ghisi on 08.11.23.
//

#ifndef AVR_TASKEXECPROMISE_H
#define AVR_TASKEXECPROMISE_H

#include "Promise.h"
#include "Task.h"

class TaskExecPromise: public Promise {
public:
    explicit TaskExecPromise(Task *task);
    ~TaskExecPromise();
    [[nodiscard]] bool isCompleted() override;
private:
    Task *task;
};

TaskExecPromise::TaskExecPromise(Task *task) {
    this->task = task;
}

bool TaskExecPromise::isCompleted() {
    return task->state == TaskState::TERMINATED;
}

TaskExecPromise::~TaskExecPromise() {

}

#endif //AVR_TASKEXECPROMISE_H
