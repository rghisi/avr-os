//
// Created by ghisi on 10.11.22.
//

#ifndef AVR_PERIODICSENSORREPORT_H
#define AVR_PERIODICSENSORREPORT_H


#include "../system/Task.h"
#include "../system/EventDispatcher.h"

class PeriodicSensorReport: public Task {
public:
    explicit PeriodicSensorReport(EventDispatcher *eventDispatcher);
    ~PeriodicSensorReport() override = default;
    void run() override;
    uint32_t delay() override;
    Type type() override;
private:
    EventDispatcher *eventDispatcher;
};


#endif //AVR_PERIODICSENSORREPORT_H
