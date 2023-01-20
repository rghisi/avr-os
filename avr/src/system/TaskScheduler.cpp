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
        auto *scheduledTask = scheduledTasks.peek();
        if (scheduledTask->timeOfExecution <= now) {
            scheduledTasks.pop();
            uint32_t userTimeStart = wallClock->now();
            scheduledTask->task->run();
            reschedule(scheduledTask);
            CpuStats::schedulerUserTime += wallClock->now() - userTimeStart;
        }
    }
}

void TaskScheduler::schedule(Task *task) {
    uint32_t nextExecution = wallClock->now() + task->delay();
    auto *scheduledTask = new ScheduledTask{.timeOfExecution = nextExecution, .task = task};
    scheduledTasks.offer(scheduledTask);
}

void TaskScheduler::reschedule(ScheduledTask *scheduledTask) {
    switch (scheduledTask->task->type()) {
        case Task::Type::SINGLE:
            delete scheduledTask;
            break;
        case Task::Type::WAIT:
            delete scheduledTask;
            break;
        case Task::Type::PERIODIC:
            uint32_t nextExecution = scheduledTask->timeOfExecution + scheduledTask->task->delay();
            scheduledTask->timeOfExecution = nextExecution;
            scheduledTasks.offer(scheduledTask);
            break;
    }
}

bool TaskScheduler::ScheduledTask::operator<(const ScheduledTask &rhs) const {
    return timeOfExecution < rhs.timeOfExecution;
}

bool TaskScheduler::ScheduledTask::operator<=(const ScheduledTask &rhs) const {
    return !(rhs < *this);
}

TaskScheduler::ScheduledTask::~ScheduledTask() {
    delete task;
}
