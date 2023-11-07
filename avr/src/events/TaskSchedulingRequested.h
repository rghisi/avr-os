//
// Created by ghisi on 12/31/22.
//

#ifndef AVR_TASKSCHEDULINGREQUESTED_H
#define AVR_TASKSCHEDULINGREQUESTED_H


#include "Message.h"
#include "../system/Task.h"

class TaskSchedulingRequested: public Message {
public:
    explicit TaskSchedulingRequested(Task* task);
    ~TaskSchedulingRequested() override;
    Task *task;
};


#endif //AVR_TASKSCHEDULINGREQUESTED_H
