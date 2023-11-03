//
// Created by ghisi on 11.03.23.
//

#include <avr/pgmspace.h>
#include "InfiniteTask.h"
#include "cstdio"
#include "cstring"
#include "../comms/SerialPacket.h"
#include "../system/OS.h"
#include "../std/Random.h"

InfiniteTask::InfiniteTask(uint8_t taskNumber) {
    this->taskNumber = taskNumber;
    nextExecution = 5 + taskNumber;
}

void InfiniteTask::run() {
    uint16_t counter = 0;
    while (true) {
        counter++;
        print(counter);
        sleep(Random::next());
        printMessage(counter);
        sleep(Random::next());
    }
}

void InfiniteTask::print(uint16_t counter) const {
    auto stringBuffer = new char[16];
    sprintf(stringBuffer, "Task %u A:%u\n", taskNumber, counter);
    auto event = new SerialPacket(reinterpret_cast<uint8_t *>(stringBuffer), strlen(stringBuffer));
    OS::send(event);
}

void InfiniteTask::printMessage(uint16_t counter) const {
    auto stringBuffer = new char[16];
    sprintf(stringBuffer, "Task %u B:%u\n", taskNumber, counter);
    auto *event = new SerialPacket(reinterpret_cast<uint8_t *>(stringBuffer), strlen(stringBuffer));
    OS::send(event);
}
