//
// Created by ghisi on 05.11.23.
//

#ifndef AVR_TASKPROMISE_H
#define AVR_TASKPROMISE_H

#include "Task.h"

class TaskPromise {
public:
    TaskPromise(Task *task, Promise *promise) {
        this->task = task;
        this->promise = promise;
    }
    ~TaskPromise() {

    }
    Task *task;
    Promise *promise;
};
#endif //AVR_TASKPROMISE_H
