//
// Created by ghisi on 13.10.22.
//

#ifndef AVR_TASKSCHEDULER_H
#define AVR_TASKSCHEDULER_H


#include "cstdint"
#include "../events/Messaging.h"
#include "Task.h"
#include "WallClock.h"
#include "../collections/StaticPriorityQueue.h"

class TaskPromise {
public:
    TaskPromise(Task *task, Promise *promise) {
        this->task = task;
        this->promise = promise;
    }
    ~TaskPromise() = default;
    Task *task;
    Promise *promise;
};

class TaskScheduler {
public:
    explicit TaskScheduler(WallClock *wallClock);
    void run();
    void schedule(Task *task);
    void add(Task *task, Promise *promise);
private:
    WallClock *wallClock;
    static StaticPriorityQueue<Task, 10> scheduledTasks;
    static BlockingQueue<TaskPromise*, 10> taskPromises;
    void processPromises();

};


#endif //AVR_TASKSCHEDULER_H
