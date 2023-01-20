//
// Created by ghisi on 15.10.22.
//

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "PeriodicCpuUsageReport.h"
#include "../networking/Packet.h"
#include "../lcd/DrawText.h"
#include "cstdio"
#include "../lcd/DisplayCommand.h"

PeriodicCpuUsageReport::PeriodicCpuUsageReport(CpuStats *cpuStats, Messaging *eventDispatcher) {
    this->cpuStats = cpuStats;
    this->eventDispatcher = eventDispatcher;
}

uint32_t PeriodicCpuUsageReport::delay() {
    return 100;
}

void PeriodicCpuUsageReport::run() {
    auto s = new char[4];
    sprintf_P(s, PSTR("%" PRIu8), cpuStats->idlePercent());
    auto event = new DrawText(13, 0, s);
    eventDispatcher->send(event);
}

Task::Type PeriodicCpuUsageReport::type() {
    return Type::PERIODIC;
}

PeriodicCpuUsageReport::~PeriodicCpuUsageReport() {
    eventDispatcher = nullptr;
    cpuStats = nullptr;
}
