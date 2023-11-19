//
// Created by ghisi on 19.03.23.
//

#ifndef AVR_PERFORMANCEREPORTER_H
#define AVR_PERFORMANCEREPORTER_H


#include "../system/StaticStack.h"
#include "../../../../../../../../../opt/avr-gcc/avr/include/avr/pgmspace.h"
#include "../system/OS.h"
#include "../../avr-libstdcpp/include/cstdio"
#include "../comms/Serial.h"
#include "../../avr-libstdcpp/include/cstring"
#include "../console/App.h"

class PerformanceReporter: public Task {
public:
    PerformanceReporter();
    void run() override;
private:
    StaticStack<64> staticStack = StaticStack<64>();
};

PerformanceReporter::PerformanceReporter(): Task(&staticStack) {

}

void PerformanceReporter::run() {
    auto memoryStats = OS::memoryStats();
    auto stringBuffer = new char[48];
    sprintf_P(
            stringBuffer,
            PSTR("U:%u\tF:%u\tBu:%u\tBf:%u\tD:%u\r\n"),
            memoryStats->used,
            memoryStats->free,
            memoryStats->usedBlocks,
            memoryStats->freeBlocks,
            memoryStats->delta
    );
    Serial::send(stringBuffer, strlen(stringBuffer));
}

class FreeApp: public App {
public:
    FreeApp() {
        name = "free";
    }

    Task* load() override {
        return new PerformanceReporter();
    }
};

#endif //AVR_PERFORMANCEREPORTER_H
