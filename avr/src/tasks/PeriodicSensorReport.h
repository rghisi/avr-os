//
// Created by ghisi on 10.11.22.
//

#ifndef AVR_PERIODICSENSORREPORT_H
#define AVR_PERIODICSENSORREPORT_H


#include "../system/Task.h"
#include "../system/Messaging.h"

class PeriodicSensorReport: public Task {
public:
    explicit PeriodicSensorReport(Messaging *eventDispatcher);
    ~PeriodicSensorReport() override = default;
    void run() override;
    uint32_t delay() override;
    Type type() override;
private:
    Messaging *eventDispatcher;
};


#endif //AVR_PERIODICSENSORREPORT_H
