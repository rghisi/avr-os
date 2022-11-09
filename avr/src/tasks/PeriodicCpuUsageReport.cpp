//
// Created by ghisi on 15.10.22.
//

#include <avr/io.h>
#include "PeriodicCpuUsageReport.h"
#include "../networking/Packet.h"

PeriodicCpuUsageReport::PeriodicCpuUsageReport(CpuStats *cpuStats, EventDispatcher *eventDispatcher) {
    this->cpuStats = cpuStats;
    this->eventDispatcher = eventDispatcher;
}

uint32_t PeriodicCpuUsageReport::delay() {
    return 100;
}

void PeriodicCpuUsageReport::run() {
    auto *stats = new CpuStats();
    stats->idleTime = cpuStats->idleTime;
    stats->usedTime = cpuStats->usedTime;
    auto event = std::make_unique<Event>(Event(EventType::CPU_STATS_DISPATCHED, stats));
    eventDispatcher->dispatch(std::move(event));
}

Task::Type PeriodicCpuUsageReport::type() {
    return Type::PERIODIC;
}

PeriodicCpuUsageReport::~PeriodicCpuUsageReport() {
    eventDispatcher = nullptr;
    cpuStats = nullptr;
}
