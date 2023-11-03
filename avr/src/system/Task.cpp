//
// Created by ghisi on 12.03.23.
//
#include "Task.h"
#include "OS.h"

bool Task::operator<(const Task &rhs) const {
    return nextExecution < rhs.nextExecution;
}

bool Task::operator>(const Task &rhs) const {
    return rhs < *this;
}

bool Task::operator<=(const Task &rhs) const {
    return !(rhs < *this);
}

bool Task::operator>=(const Task &rhs) const {
    return !(*this < rhs);
}

void Task::yield() {
    nextExecution = 0;
    OS::yield(this);
}

void Task::sleep(uint16_t ms) {
    nextExecution = ms;
    OS::yield(this);
}
