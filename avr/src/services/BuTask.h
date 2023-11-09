//
// Created by ghisi on 03.11.23.
//

#ifndef AVR_BUTASK_H
#define AVR_BUTASK_H

#include "cstring"
#include "cstdio"
#include "../comms/Serial.h"
#include "../system/HeapTask.h"

class BuTask: public HeapTask {
public:
    BuTask();
    ~BuTask() override = default;
    void run() override;
};

BuTask::BuTask(): HeapTask(96) {

}

void BuTask::run() {
    Serial::send("Bu!\n", 4);
    yield();
}


#endif //AVR_BUTASK_H
