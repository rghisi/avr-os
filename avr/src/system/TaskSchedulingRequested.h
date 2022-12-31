//
// Created by ghisi on 12/31/22.
//

#ifndef AVR_TASKSCHEDULINGREQUESTED_H
#define AVR_TASKSCHEDULINGREQUESTED_H


#include "Event.h"
#include "Task.h"

class TaskSchedulingRequested: public Event {
public:
    explicit TaskSchedulingRequested(Task* task);
    ~TaskSchedulingRequested() override;
    Task *task;
};


#endif //AVR_TASKSCHEDULINGREQUESTED_H
