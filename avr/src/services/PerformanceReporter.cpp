//
// Created by ghisi on 12.11.23.
//

#include <avr/pgmspace.h>
#include "PerformanceReporter.h"
#include "../system/OS.h"
#include "cstdio"
#include "../comms/Serial.h"
#include "cstring"
#include "../system/CpuStats.h"
#include "../system/HeapStack.h"

PerformanceReporter::PerformanceReporter(): PeriodicTask(&staticStack) {

}

void PerformanceReporter::run() {
    executions++;
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

uint_fast16_t PerformanceReporter::period() {
    return PERIOD;
}
