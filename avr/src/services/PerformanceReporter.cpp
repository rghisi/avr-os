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
        sleep(1000);
    }
}

void PerformanceReporter::send() {
    auto memoryStats = OS::memoryStats();
    auto stringBuffer = new char[36];
    sprintf_P(
            stringBuffer,
            PSTR("C:%u\tS:%u\tE:%u\tM:%u\tU:%u\tF:%u\n"),
            executions,
            CpuStats::schedulerUserTime,
            CpuStats::eventLoopUserTime,
            memoryStats->used,
            memoryStats->usedBlocks,
            memoryStats->freeBlocks
            );
    Serial::send(stringBuffer, strlen(stringBuffer));
//    auto event = new SerialPacket(reinterpret_cast<uint8_t *>(stringBuffer), strlen(stringBuffer));
//    OS::send(event);
    CpuStats::schedulerUserTime = 0;
    CpuStats::eventLoopUserTime = 0;
}
