//
// Created by ghisi on 27.10.22.
//

#ifndef AVR_PERIODICMEMORYREPORT_H
#define AVR_PERIODICMEMORYREPORT_H


#include "../system/Task.h"
#include "../system/EventDispatcher.h"
#include "../system/MemoryStats.h"
#include "../system/WallClock.h"

class PeriodicMemoryReport: public Task {
public:
    explicit PeriodicMemoryReport(EventDispatcher *eventDispatcher);
    ~PeriodicMemoryReport() override;
    void run() override;
    uint32_t delay() override;
    Type type() override;
private:
    EventDispatcher *eventDispatcher;
};


#endif //AVR_PERIODICMEMORYREPORT_H
