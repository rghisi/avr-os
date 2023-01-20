//
// Created by ghisi on 1/17/23.
//

#ifndef AVR_CPUUSAGEREPORT_H
#define AVR_CPUUSAGEREPORT_H


#include "../../system/Message.h"

class CpuUsageReport: public Message {
public:
    CpuUsageReport(uint16_t schedulerUserTime, uint16_t eventLoopUserTime);
    uint16_t schedulerUserTime;
    uint16_t eventLoopUserTime;
};


#endif //AVR_CPUUSAGEREPORT_H
