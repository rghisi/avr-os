//
// Created by ghisi on 03.11.23.
//

#ifndef AVR_BUTASK_H
#define AVR_BUTASK_H

#include "../../avr-libstdcpp/include/cstring"
#include "../../avr-libstdcpp/include/cstdio"
#include "../comms/Serial.h"
#include "../system/Task.h"
#include "../system/StaticStack.h"
#include "../console/App.h"

class BuTask: public Task {
public:
    BuTask();
    ~BuTask() = default;
    void run() override;
};

BuTask::BuTask(): Task(new StaticStack<64>()) {

}

void BuTask::run() {
    Serial::send("Wait for it...", 15);
    sleep(1000);
    Serial::send("Bu!\r\n", 5);
}

class BuApp: public App {
public:
    BuApp() {
        name = "bu";
    }

    Task* load(char* args) override {
        return new BuTask();
    }
};

#endif //AVR_BUTASK_H
