//
// Created by ghisi on 15.10.22.
//

#include "PeriodicCpuUsageReport.h"
#include "../networking/Packet.h"

PeriodicCpuUsageReport::PeriodicCpuUsageReport(CpuStats *cpuStats, EventDispatcher *eventDispatcher) {
    this->cpuStats = cpuStats;
    this->eventDispatcher = eventDispatcher;
}

uint32_t PeriodicCpuUsageReport::delay() {
    return 2000;
}

void PeriodicCpuUsageReport::run() {
    eventDispatcher->dispatch(new Event(EventType::CPU_STATS_DISPATCHED, cpuStats));
}

Task::Type PeriodicCpuUsageReport::type() {
    return Type::PERIODIC;
}

PeriodicCpuUsageReport::~PeriodicCpuUsageReport() {
    eventDispatcher = nullptr;
    cpuStats = nullptr;
}
