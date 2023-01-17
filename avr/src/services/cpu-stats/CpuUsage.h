//
// Created by ghisi on 15.10.22.
//

#ifndef AVR_CPUUSAGE_H
#define AVR_CPUUSAGE_H


#include "../../system/Messaging.h"
#include "../../system/CpuStats.h"
#include "../../system/Task.h"

class CpuUsage: public Task {
public:
    explicit CpuUsage(Messaging *messaging);
    ~CpuUsage() override;
    uint32_t delay() override;
    void run() override;
    Type type() override;

private:
    Messaging *messaging;
};


#endif //AVR_CPUUSAGE_H
