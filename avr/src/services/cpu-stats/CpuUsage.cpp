//
// Created by ghisi on 15.10.22.
//

#include "CpuUsage.h"
#include "../../networking/Packet.h"
#include "../../lcd/DrawText.h"
#include "CpuUsageReport.h"

CpuUsage::CpuUsage(Messaging *messaging) {
    this->messaging = messaging;
}

uint32_t CpuUsage::delay() {
    return 1000;
}

void CpuUsage::run() {
    messaging->send(
    new CpuUsageReport(
            CpuStats::schedulerUserTime,
            CpuStats::eventLoopUserTime
        )
    );
    CpuStats::schedulerUserTime = 0;
    CpuStats::eventLoopUserTime = 0;
}

Task::Type CpuUsage::type() {
    return Type::PERIODIC;
}

CpuUsage::~CpuUsage() {
    messaging = nullptr;
}
