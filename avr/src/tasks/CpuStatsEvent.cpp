//
// Created by ghisi on 12/31/22.
//

#include "CpuStatsEvent.h"

CpuStatsEvent::CpuStatsEvent(CpuStats *cpuStats) : Event(EventType::CPU_STATS_READ) {
    this->cpuStats = cpuStats;
}

CpuStatsEvent::~CpuStatsEvent() {

}

CpuStats *CpuStatsEvent::stats() {
    return cpuStats;
}
