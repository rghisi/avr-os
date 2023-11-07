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
#include "TaskPromise.h"

class TaskScheduler {
public:
    explicit TaskScheduler(WallClock *wallClock, EventLoop *pLoop);
    void run();
    void schedule(Task *task);
    void add(TaskPromise *taskPromise);
private:
    WallClock *wallClock;
    EventLoop *eventLoop;
    static StaticPriorityQueue<Task, 10> scheduledTasks;
    static BlockingQueue<TaskPromise*, 10> taskPromises;

    void reschedule(Task *task);

    void processPromises();
};


#endif //AVR_TASKSCHEDULER_H
