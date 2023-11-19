//
// Created by ghisi on 03.11.23.
//

#ifndef AVR_PITASK_H
#define AVR_PITASK_H

#include "../../../../../../../../../opt/avr-gcc/avr/include/avr/pgmspace.h"
#include "../system/OS.h"
#include "cstring"
#include "cstdio"
#include "../comms/Serial.h"
#include "complex"
#include "../system/HeapStack.h"
#include "../console/App.h"

class PiTask: public Task {
public:
    PiTask();
    void run() override;
private:
    double bestPi = 0;
    double newPi = 0;
    double n = 0;
    double sign = 0;
    uint_fast8_t iterations = 0;
};

PiTask::PiTask(): Task(new HeapStack(128)) {
}

void PiTask::run() {
    auto sb = new char[18];
    sprintf_P(sb, PSTR("Calculating PI: "));
    Serial::send(sb, strlen(sb));

    bestPi = 0;
    newPi = 3.0;
    n = 2;
    sign = 1.0;
    do {
        bestPi = newPi;
        newPi += sign * (4.0 / ((n) * (n + 1) * (n + 2)));
        sign = sign * (-1.0);
        n += 2;
        iterations++;
    } while (std::abs(newPi - bestPi) > 0.000001);

    auto stringBuffer = new char[18];
    sprintf_P(stringBuffer, PSTR("%f (%u)\n\r"), bestPi, iterations);
    Serial::send(stringBuffer, strlen(stringBuffer));
}

class PiApp: public App {
public:
    PiApp() {
        name = "pi";
    }

    Task* load() override {
        return new PiTask();
    }
};

#endif //AVR_PITASK_H
