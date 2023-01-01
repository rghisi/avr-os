//
// Created by ghisi on 27.10.22.
//

#ifndef AVR_PERIODICMEMORYREPORT_H
#define AVR_PERIODICMEMORYREPORT_H

#include "../system/Task.h"
#include "../system/MessageDispatcher.h"

class PeriodicMemoryReport: public Task {
public:
    explicit PeriodicMemoryReport(MessageDispatcher *eventDispatcher);
    ~PeriodicMemoryReport() override;
    void run() override;
    uint32_t delay() override;
    Type type() override;
private:
    MessageDispatcher *eventDispatcher;
};


#endif //AVR_PERIODICMEMORYREPORT_H
