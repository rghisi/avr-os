//
// Created by ghisi on 1/17/23.
//

#include "CpuUsageReport.h"

CpuUsageReport::CpuUsageReport(uint16_t schedulerUserTime, uint16_t eventLoopUserTime): Message(MessageType::CPU_REPORT) {
    this->schedulerUserTime = schedulerUserTime;
    this->eventLoopUserTime = eventLoopUserTime;
}
