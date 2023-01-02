//
// Created by ghisi on 27.10.22.
//

#ifndef AVR_PERIODICMEMORYREPORT_H
#define AVR_PERIODICMEMORYREPORT_H

#include "../system/Task.h"
#include "../system/Messaging.h"

class PeriodicMemoryReport: public Task {
public:
    explicit PeriodicMemoryReport(Messaging *eventDispatcher);
    ~PeriodicMemoryReport() override;
    void run() override;
    uint32_t delay() override;
    Type type() override;
private:
    Messaging *eventDispatcher;
};


#endif //AVR_PERIODICMEMORYREPORT_H
