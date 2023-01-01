//
// Created by ghisi on 15.10.22.
//

#include <avr/io.h>
#include "PeriodicCpuUsageReport.h"
#include "../networking/Packet.h"
#include "../lcd/DrawText.h"
#include "cstdio"
#include "../lcd/DisplayCommand.h"

PeriodicCpuUsageReport::PeriodicCpuUsageReport(CpuStats *cpuStats, MessageDispatcher *eventDispatcher) {
    this->cpuStats = cpuStats;
    this->eventDispatcher = eventDispatcher;
}

uint32_t PeriodicCpuUsageReport::delay() {
    return 100;
}

void PeriodicCpuUsageReport::run() {
    auto s = new char[4];
    sprintf(s, "%" PRIu8, cpuStats->idlePercent());
    auto event = DisplayCommand::drawText(13, 0, s);
    eventDispatcher->dispatch(event);
}

Task::Type PeriodicCpuUsageReport::type() {
    return Type::PERIODIC;
}

PeriodicCpuUsageReport::~PeriodicCpuUsageReport() {
    eventDispatcher = nullptr;
    cpuStats = nullptr;
}
