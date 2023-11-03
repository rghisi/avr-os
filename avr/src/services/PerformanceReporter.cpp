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

void PerformanceReporter::run() {
    while (true) {
        executions++;
        send();
        sleep(1000);
    }
}

void PerformanceReporter::send() const {
    auto stringBuffer = new char[36];
    sprintf(stringBuffer, "C:%u S:%u E:%u M:%u\n", executions, CpuStats::schedulerUserTime, CpuStats::eventLoopUserTime, OS::usedMemory());
    auto event = new SerialPacket(reinterpret_cast<uint8_t *>(stringBuffer), strlen(stringBuffer));
    OS::send(event);
    CpuStats::schedulerUserTime = 0;
    CpuStats::eventLoopUserTime = 0;
}
