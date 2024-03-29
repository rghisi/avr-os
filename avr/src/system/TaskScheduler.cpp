//
// Created by ghisi on 13.10.22.
//

#include "TaskScheduler.h"
#include "OS.h"
#include "cstdio"
#include "cstring"

BlockingQueue<Task*, 10> TaskScheduler::scheduledTasks = BlockingQueue<Task*, 10>();
StaticPriorityQueue<PeriodicScheduledTask, 10> TaskScheduler::periodicTasks = StaticPriorityQueue<PeriodicScheduledTask, 10>();
BlockingQueue<TaskPromise*, 10> TaskScheduler::taskPromises = BlockingQueue<TaskPromise*, 10>();

TaskScheduler::TaskScheduler() {
}

void TaskScheduler::schedule(Task *task) {
    scheduledTasks.offer(task);
}

void TaskScheduler::schedule(PeriodicTask *task) {
    auto *periodicScheduledTask = new PeriodicScheduledTask(task);
    periodicScheduledTask->nextExecution = WallClock::now + task->period();
    periodicTasks.offer(periodicScheduledTask);
}

void TaskScheduler::add(Task *task, Promise *promise) {
    if (!taskPromises.isFull()) {
        taskPromises.offer(new TaskPromise(task, promise));
    }
}

[[noreturn]] void TaskScheduler::run() {
    while (true) {
        processPromises();
        processPeriodicTasks();
        processRegularTasks();
    }
}

void TaskScheduler::processPromises() {
    auto promises = taskPromises.itemCount();
    for (uint_fast8_t i = 0; i < promises; i++) {
        auto taskPromise = taskPromises.poll();
        if (taskPromise->promise->isCompleted()) {
            taskPromise->task->state = TaskState::WAITING;
            delete taskPromise;
        } else {
            taskPromises.offer(taskPromise);
        }
    }
}

void TaskScheduler::processPeriodicTasks() {
    if (!periodicTasks.isEmpty()) {
        auto *periodicScheduledTask = periodicTasks.peek();
        auto now = WallClock::now;
        while (periodicScheduledTask->nextExecution <= now) {
            periodicTasks.pop();
            auto *periodicTask = periodicScheduledTask->task;
            periodicTask->state = TaskState::RUNNING;
            OS::startTask(periodicTask);
            periodicTask->state = TaskState::WAITING;
            periodicScheduledTask->nextExecution = now + periodicTask->period();
            periodicTasks.offer(periodicScheduledTask);
            periodicScheduledTask = periodicTasks.peek();
        }
    }
}

void TaskScheduler::processRegularTasks() {
    if (!scheduledTasks.isEmpty()) {
        auto *task = scheduledTasks.poll();
        if (task->state != TaskState::TERMINATED) {
            if (task->state == TaskState::CREATED) {
                task->state = TaskState::RUNNING;
                OS::startTask(task);
                if (task->state == TaskState::RUNNING) {
                    task->state = TaskState::TERMINATED;
                }
            } else if (task->state == TaskState::WAITING) {
                task->state = TaskState::RUNNING;
                OS::switchToTask(task);
            }
            schedule(task);
        } else {
            delete task;
        }
    }
}

Task *TaskScheduler::getNext() {
    return nullptr;
}

//void TaskScheduler::processRegularTasks() {
//    if (!scheduledTasks.isEmpty()) {
//        auto now = WallClock::now;
//        auto *task = scheduledTasks.peek();
//        if (task->nextExecution <= now) {
//            scheduledTasks.pop();
//            if (task->state != TaskState::TERMINATED) {
//                if (task->state == TaskState::CREATED) {
//                    task->state = TaskState::RUNNING;
//                    OS::startTask(task);
//                    if (task->state == TaskState::RUNNING) {
//                        task->state = TaskState::TERMINATED;
//                    }
//                } else if (task->state == TaskState::WAITING) {
//                    task->state = TaskState::RUNNING;
//                    OS::switchToTask(task);
//                }
//                schedule(task);
//            }
//        }
//    }
//}
