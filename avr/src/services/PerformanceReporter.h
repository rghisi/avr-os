//
// Created by ghisi on 19.03.23.
//

#ifndef AVR_PERFORMANCEREPORTER_H
#define AVR_PERFORMANCEREPORTER_H


#include "../system/PeriodicTask.h"
#include "../system/StaticStack.h"

class PerformanceReporter: public PeriodicTask {
public:
    PerformanceReporter();
    void run() override;
    uint_fast16_t period() override;
    uint16_t executions = 0;
private:
    StaticStack<64> staticStack = StaticStack<64>();
    const uint_fast16_t PERIOD = 1000;
};

#endif //AVR_PERFORMANCEREPORTER_H
