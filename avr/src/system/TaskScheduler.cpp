//
// Created by ghisi on 13.10.22.
//

#include "TaskScheduler.h"
#include "CpuStats.h"
#include "OS.h"
#include "cstdio"
#include "cstring"
#include "../comms/Serial.h"

StaticPriorityQueue<Task, 10> TaskScheduler::scheduledTasks = StaticPriorityQueue<Task, 10>();
BlockingQueue<TaskPromise*, 10> TaskScheduler::taskPromises = BlockingQueue<TaskPromise*, 10>();

TaskScheduler::TaskScheduler(WallClock *wallClock) {
    this->wallClock = wallClock;
}

void TaskScheduler::schedule(Task *task) {
    if (task->state == TaskState::TERMINATED) {
        task->nextExecution = 0;
    } else {
        task->nextExecution += wallClock->now;
    }
    scheduledTasks.offer(task);
}

void TaskScheduler::run() {
    while (true) {
        processPromises();
        if (!scheduledTasks.isEmpty()) {
            uint32_t now = wallClock->now;
            auto *task = scheduledTasks.peek();
            if (task->nextExecution <= now) {
                scheduledTasks.pop();
                uint32_t userTimeStart = wallClock->now;
                if (task->state != TaskState::TERMINATED) {
                    if (task->state == TaskState::CREATED) {
                        OS::startTask(task);
                    } else if (task->state == TaskState::WAITING) {
                        task->state = TaskState::RUNNING;
                        OS::switchToTask(task);
                    }
                    schedule(task);
                }
                CpuStats::schedulerUserTime += wallClock->now - userTimeStart;
            }
        }
    }
}

void TaskScheduler::processPromises() {
    auto promises = taskPromises.itemCount();
    for (uint_fast8_t i = 0; i < promises; i++) {
        auto taskPromise = taskPromises.poll();
        if (taskPromise->promise->isCompleted()) {
            taskPromise->task->state = TaskState::WAITING;
            taskPromise->task->nextExecution = 0;
            delete taskPromise;
        } else {
            taskPromises.offer(taskPromise);
        }
    }
}

void TaskScheduler::add(Task *task, Promise *promise) {
    if (!taskPromises.isFull()) {
        taskPromises.offer(new TaskPromise(task, promise));
    }
}
