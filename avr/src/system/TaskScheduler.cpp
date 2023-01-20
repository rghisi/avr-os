//
// Created by ghisi on 13.10.22.
//

#include <avr/io.h>
#include "TaskScheduler.h"
#include "../collections/PriorityQueue.cpp"
#include "CpuStats.h"

TaskScheduler::TaskScheduler(WallClock *wallClock) {
    this->wallClock = wallClock;
}

void TaskScheduler::process() {
    if (!scheduledTasks.isEmpty()) {
        uint32_t now = wallClock->now();
        auto *task = scheduledTasks.peek();
        if (task->nextExecution <= now) {
            scheduledTasks.pop();
            uint32_t userTimeStart = wallClock->now();
            task->run();
            reschedule(task);
            CpuStats::schedulerUserTime += wallClock->now() - userTimeStart;
        }
    }
}

void TaskScheduler::schedule(Task *task) {
    auto delay = scheduleSeed++;
    if (task->type() == Task::Type::WAIT) {
        delay = task->delay();
    }
    task->nextExecution = wallClock->now() + delay;
    scheduledTasks.offer(task);
}

void TaskScheduler::reschedule(Task *task) {
    switch (task->type()) {
        case Task::Type::SINGLE:
            delete task;
            break;
        case Task::Type::WAIT:
            delete task;
            break;
        case Task::Type::PERIODIC:
            task->nextExecution += task->delay();
            scheduledTasks.offer(task);
            break;
    }
}
