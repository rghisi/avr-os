//
// Created by ghisi on 08.03.24.
//

#ifndef AVR_PROCESS_H
#define AVR_PROCESS_H


#include "../system/Task.h"
#include "../system/StaticStack.h"
#include "cstdint"
#include "../console/App.h"

class Process: public Task {
public:
    Process(int_fast8_t (*entryPoint)(char*), char* args);
    ~Process() = default;
    void run() override;
private:
    int_fast8_t (*entryPoint)(char *);
    char *args;
};

Process::Process(int_fast8_t (*entryPoint)(char *), char *args) : Task(new StaticStack<128>()) {
    this->entryPoint = entryPoint;
    this->args = args;
}

void Process::run() {
    entryPoint(args);
}

class ProcessApp: public App {
public:
    ProcessApp(const char* commandName, int_fast8_t (*entryPoint)(char*)) {
        name = commandName;
        this->entryPoint = entryPoint;
    }

    Task* load(char* args) override {
        return new Process(entryPoint, args);
    }
private:
    int_fast8_t (*entryPoint)(char *);
};

#endif //AVR_PROCESS_H
