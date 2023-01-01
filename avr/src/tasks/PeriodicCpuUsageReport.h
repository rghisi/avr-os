//
// Created by ghisi on 15.10.22.
//

#ifndef AVR_PERIODICCPUUSAGEREPORT_H
#define AVR_PERIODICCPUUSAGEREPORT_H


#include "../system/MessageDispatcher.h"
#include "../system/CpuStats.h"
#include "../system/Task.h"

class PeriodicCpuUsageReport: public Task {
public:
    PeriodicCpuUsageReport(CpuStats *cpuStats, MessageDispatcher *eventDispatcher);
    ~PeriodicCpuUsageReport() override;
    uint32_t delay() override;
    void run() override;
    Type type() override;

private:
    MessageDispatcher *eventDispatcher;
    CpuStats *cpuStats;
};


#endif //AVR_PERIODICCPUUSAGEREPORT_H
