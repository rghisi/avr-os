//
// Created by ghisi on 12/31/22.
//

#ifndef AVR_CPUSTATSEVENT_H
#define AVR_CPUSTATSEVENT_H


#include "../system/Event.h"
#include "../system/CpuStats.h"

class CpuStatsEvent: public Event {
public:
    CpuStatsEvent(CpuStats *cpuStats);
    ~CpuStatsEvent();
    CpuStats* stats();
private:
    CpuStats *cpuStats;
};


#endif //AVR_CPUSTATSEVENT_H
