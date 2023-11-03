//
// Created by ghisi on 13.10.22.
//

#ifndef AVR_TASKSCHEDULER_H
#define AVR_TASKSCHEDULER_H


#include "cstdint"
#include "Messaging.h"
#include "Task.h"
#include "WallClock.h"
#include "../collections/StaticPriorityQueue.h"

class TaskScheduler {
public:
    explicit TaskScheduler(WallClock *wallClock, EventLoop *pLoop);
    void run();
    void schedule(Task *task);
private:
    WallClock *wallClock;
    EventLoop *eventLoop;
    StaticPriorityQueue<Task*, 6> scheduledTasks;
    void reschedule(Task *task);
};


#endif //AVR_TASKSCHEDULER_H
