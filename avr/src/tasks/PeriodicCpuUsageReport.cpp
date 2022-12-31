//
// Created by ghisi on 15.10.22.
//

#include <avr/io.h>
#include "PeriodicCpuUsageReport.h"
#include "../networking/Packet.h"
#include "CpuStatsEvent.h"

PeriodicCpuUsageReport::PeriodicCpuUsageReport(CpuStats *cpuStats, EventDispatcher *eventDispatcher) {
    this->cpuStats = cpuStats;
    this->eventDispatcher = eventDispatcher;
}

uint32_t PeriodicCpuUsageReport::delay() {
    return 100;
}

void PeriodicCpuUsageReport::run() {
    auto event = new CpuStatsEvent(cpuStats);
    eventDispatcher->dispatch(event);
}

Task::Type PeriodicCpuUsageReport::type() {
    return Type::PERIODIC;
}

PeriodicCpuUsageReport::~PeriodicCpuUsageReport() {
    eventDispatcher = nullptr;
    cpuStats = nullptr;
}
