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
#include "PeriodicTask.h"

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

class PeriodicScheduledTask {
public:
    explicit PeriodicScheduledTask(PeriodicTask *task) {
        this->task = task;
        nextExecution = 0;
    }
    ~PeriodicScheduledTask() = default;

    bool operator<(const PeriodicScheduledTask &rhs) const {
        return nextExecution < rhs.nextExecution;
    }

    bool operator>(const PeriodicScheduledTask &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const PeriodicScheduledTask &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const PeriodicScheduledTask &rhs) const {
        return !(*this < rhs);
    }

    PeriodicTask *task;
    volatile uint_fast32_t nextExecution;
};

class TaskScheduler {
public:
    explicit TaskScheduler();

    [[noreturn]] void run();
    void schedule(Task *task);
    void schedule(PeriodicTask *task);
    void add(Task *task, Promise *promise);
private:
    static BlockingQueue<Task*, 10> scheduledTasks;
    static StaticPriorityQueue<PeriodicScheduledTask, 10> periodicTasks;
    static BlockingQueue<TaskPromise*, 10> taskPromises;
    void processPromises();
    void processPeriodicTasks();
    void processRegularTasks();

};


#endif //AVR_TASKSCHEDULER_H
