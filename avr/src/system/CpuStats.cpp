//
// Created by ghisi on 17.10.22.
//

#include "CpuStats.h"

void CpuStats::start(uint32_t startTimestamp) {
    this->startTimestamp = startTimestamp;
}

void CpuStats::end(uint32_t endTimestamp, bool usedNotIdle) {
    auto delta = endTimestamp - startTimestamp;
    if (s == UINT16_MAX) {
        usedTime = 0;
        idleTime = 0;
    }
    if (usedNotIdle) {
        usedTime += delta;
    } else {
        idleTime += delta;
    }
    s++;
}

uint8_t CpuStats::idlePercent() {
    uint32_t total = usedTime + idleTime;
    return (idleTime * 100) / total;
}
