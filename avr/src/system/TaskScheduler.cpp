//
// Created by ghisi on 13.10.22.
//

#include <util/delay.h>
#include "TaskScheduler.h"
#include "../collections/StaticPriorityQueue.cpp"
#include "CpuStats.h"
#include "OS.h"

TaskScheduler::TaskScheduler(WallClock *wallClock, EventLoop *eventLoop) {
    this->wallClock = wallClock;
    this->eventLoop = eventLoop;
}

void TaskScheduler::schedule(Task *task) {
    task->nextExecution += wallClock->now();
    scheduledTasks.offer(task);
}

void TaskScheduler::reschedule(Task *task) {
    task->nextExecution += wallClock->now();
    scheduledTasks.offer(task);
}

void TaskScheduler::run() {
    eventLoop->process();
    if (!scheduledTasks.isEmpty()) {
        uint32_t now = wallClock->now();
        auto *task = scheduledTasks.peek();
        if (task->nextExecution <= now) {
            scheduledTasks.pop();
            uint32_t userTimeStart = wallClock->now();
            if (task->state == TaskState::CREATED) {
                task->state = TaskState::RUNNING;
                OS::startTask(task);
            } else {
                OS::switchToTask(task);
            }
            reschedule(task);
            CpuStats::schedulerUserTime += wallClock->now() - userTimeStart;
        }
    }
}