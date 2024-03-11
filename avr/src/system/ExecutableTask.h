//
// Created by ghisi on 09.03.24.
//

#ifndef AVR_EXECUTABLETASK_H
#define AVR_EXECUTABLETASK_H


#include "Task.h"

class ExecutableTask: public Task {
public:
    ExecutableTask(int_fast8_t (*entryPoint)(char *), char *args);
    ~ExecutableTask() override;
    void execute() override;
private:
    int_fast8_t (*entryPointFunction)(char *);
    char *args;
};

ExecutableTask::ExecutableTask(int_fast8_t (*entryPoint)(char *), char *args) {
    this->entryPointFunction = entryPoint;
    this->args = args;
    state = TaskState::CREATED;
}

void ExecutableTask::execute() {
    state = TaskState::RUNNING;
    entryPointFunction(args);
    state = TaskState::TERMINATED;
}

ExecutableTask::~ExecutableTask() {
    //delete args;
}


#endif //AVR_EXECUTABLETASK_H
