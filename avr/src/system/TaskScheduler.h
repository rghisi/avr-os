//
// Created by ghisi on 13.10.22.
//

#ifndef AVR_TASKSCHEDULER_H
#define AVR_TASKSCHEDULER_H


#include "cstdint"
#include "MessageDispatcher.h"
#include "Task.h"
#include "WallClock.h"
#include "../collections/PriorityQueue.h"

class TaskScheduler {
public:
    explicit TaskScheduler(WallClock *wallClock);
    void schedule(Task *task);
    bool process();
private:
    struct ScheduledTask {
        uint32_t timeOfExecution;
        Task *task;
        ~ScheduledTask();
        bool operator<(const ScheduledTask &rhs) const;
        bool operator<=(const ScheduledTask &rhs) const;
    };
    WallClock *wallClock;
    PriorityQueue<ScheduledTask*> scheduledTasks;
    void reschedule(ScheduledTask *scheduledTask, uint32_t now);
};


#endif //AVR_TASKSCHEDULER_H
