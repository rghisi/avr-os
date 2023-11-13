//
// Created by ghisi on 03.11.23.
//

#ifndef AVR_PITASK_H
#define AVR_PITASK_H

#include <avr/pgmspace.h>
#include "../system/OS.h"
#include "cstring"
#include "cstdio"
#include "../comms/Serial.h"
#include "complex"
#include "../system/HeapStack.h"

class PiTask: public Task {
public:
    PiTask();
    void run() override;
    double pi = 0;
    double npi = 0;
private:
    double n = 0;
    double sign = 0;
    uint32_t nn = 0;
};

PiTask::PiTask(): Task(new HeapStack(128)) {
}

void PiTask::run() {
    auto sb = new char[18];
    sprintf_P(sb, PSTR("Calculating PI: "));
    Serial::send(sb, strlen(sb));

    pi = 0;
    npi = 3.0;
    n = 2;
    sign = 1.0;
    nn = 0;
    do {
        pi = npi;
        npi += sign * (4.0 / ((n) * (n + 1) * (n + 2)));
        sign = sign * (-1.0);
        n += 2;
        nn++;
//        if (nn % 2 == 0) {
//            auto stringBuffer = new char[10];
//            sprintf_P(stringBuffer, PSTR("%f\n"), pi);
//            await(Serial::sendAsync(stringBuffer, strlen(stringBuffer)));
////            sleep(50);
//        }
    } while (std::abs(npi - pi) > 0.000001);

    auto stringBuffer = new char[10];
    sprintf_P(stringBuffer, PSTR("%f\n"), pi);
    Serial::send(stringBuffer, strlen(stringBuffer));
}

#endif //AVR_PITASK_H
