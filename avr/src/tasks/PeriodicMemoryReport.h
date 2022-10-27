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
    explicit PeriodicMemoryReport(WallClock *wallClock, EventDispatcher *eventDispatcher);
    ~PeriodicMemoryReport() override;
    void run() override;
    uint32_t delay() override;
    Type type() override;
private:
    EventDispatcher *eventDispatcher;
    MemoryStats memoryStats;
    WallClock *wallClock;
    uint32_t now;
};


#endif //AVR_PERIODICMEMORYREPORT_H
