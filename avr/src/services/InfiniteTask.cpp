//
// Created by ghisi on 11.03.23.
//

#include <avr/pgmspace.h>
#include "InfiniteTask.h"
#include "cstdio"
#include "cstring"
#include "../std/Random.h"
#include "../comms/Serial.h"

InfiniteTask::InfiniteTask(uint8_t taskNumber) {
    this->taskNumber = taskNumber;
    nextExecution = 5 + taskNumber;
}

void InfiniteTask::run() {
    uint16_t counter = 0;
    uint8_t sleepAmount;
    while (true) {
        counter++;
        sleepAmount = Random::next();
        print(counter, sleepAmount);
        sleep(sleepAmount);
        sleepAmount = Random::next();
        printMessage(counter, sleepAmount);
        sleep(Random::next());
    }
}

void InfiniteTask::print(uint16_t counter, uint8_t sleep) {
    auto stringBuffer = new char[20];
    sprintf_P(stringBuffer, PSTR("T %u A:%u S:%u\n"), taskNumber, counter, sleep);
    await(Serial::sendAsync(stringBuffer, strlen(stringBuffer)));
}

void InfiniteTask::printMessage(uint16_t counter, uint8_t sleep) {
    auto stringBuffer = new char[20];
    sprintf_P(stringBuffer, PSTR("T %u B:%u S:%u\n"), taskNumber, counter, sleep);
    Serial::send(stringBuffer, strlen(stringBuffer));
}
