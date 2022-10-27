//
// Created by ghisi on 17.10.22.
//

#include "CpuStats.h"

void CpuStats::start(uint32_t startTimestamp) {
    this->startTimestamp = startTimestamp;
}

void CpuStats::end(uint32_t endTimestamp, bool usedNotIdle) {
    auto delta = endTimestamp - startTimestamp;
    if (usedNotIdle) {
        usedTime += delta;
    } else {
        idleTime += delta;
    }
}

uint8_t CpuStats::idlePercent() {
    uint32_t total = usedTime + idleTime;
    return (idleTime * 100) / total;
}
