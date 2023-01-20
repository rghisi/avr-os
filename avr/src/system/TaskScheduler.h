//
// Created by ghisi on 13.10.22.
//

#ifndef AVR_TASKSCHEDULER_H
#define AVR_TASKSCHEDULER_H


#include "cstdint"
#include "Messaging.h"
#include "Task.h"
#include "WallClock.h"
#include "../collections/PriorityQueue.h"

class TaskScheduler {
public:
    explicit TaskScheduler(WallClock *wallClock);
    void schedule(Task *task);
    void process();
private:
    WallClock *wallClock;
    PriorityQueue<Task*> scheduledTasks;
    void reschedule(Task *task);
};


#endif //AVR_TASKSCHEDULER_H
