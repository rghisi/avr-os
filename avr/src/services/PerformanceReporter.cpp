//
// Created by ghisi on 19.03.23.
//

#include <avr/pgmspace.h>
#include "PerformanceReporter.h"
#include "../system/OS.h"
#include "../comms/SerialPacket.h"
#include "cstring"
#include "../system/CpuStats.h"
#include "cstdio"
#include "../comms/Serial.h"

void PerformanceReporter::run() {
    while (true) {
        executions++;
        send();
        sleep(100);
    }
}

void PerformanceReporter::send() {
    auto memoryStats = OS::memoryStats();
    auto stringBuffer = new char[48];
    sprintf_P(
            stringBuffer,
            PSTR("C:%u\tU:%u\tF:%u\tBu:%u\tBf:%u\tD:%u\n"),
            executions,
//            CpuStats::schedulerUserTime,
//            CpuStats::eventLoopUserTime,
            memoryStats->used,
            memoryStats->free,
            memoryStats->usedBlocks,
            memoryStats->freeBlocks,
            memoryStats->delta
            );
    Serial::send(stringBuffer, strlen(stringBuffer));
    CpuStats::schedulerUserTime = 0;
    CpuStats::eventLoopUserTime = 0;
}
