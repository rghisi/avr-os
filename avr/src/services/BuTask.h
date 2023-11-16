//
// Created by ghisi on 03.11.23.
//

#ifndef AVR_BUTASK_H
#define AVR_BUTASK_H

#include "cstring"
#include "cstdio"
#include "../comms/Serial.h"
#include "../system/Task.h"
#include "../system/StaticStack.h"

class BuTask: public Task {
public:
    BuTask();
    ~BuTask() = default;
    void run() override;
};

BuTask::BuTask(): Task(new StaticStack<64>()) {

}

void BuTask::run() {
    Serial::send("Bu!\r\n", 5);
}


#endif //AVR_BUTASK_H
