//
// Created by ghisi on 13.10.22.
//

#include <avr/io.h>
#include "TaskScheduler.h"
#include "../collections/PriorityQueue.cpp"

TaskScheduler::TaskScheduler(WallClock *wallClock) {
    this->wallClock = wallClock;
}

bool TaskScheduler::process() {
    if (!scheduledTasks.isEmpty()) {
        uint32_t now = wallClock->now();
        auto *task = scheduledTasks.peek();
        if (task->nextExecution <= now) {
            scheduledTasks.pop();
            task->run();
            reschedule(task);
            return true;
        }
    }

    return false;
}

void TaskScheduler::schedule(Task *task) {
    task->nextExecution = wallClock->now() + scheduleSeed++;
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
