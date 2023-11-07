//
// Created by ghisi on 19.03.23.
//

#ifndef AVR_PERFORMANCEREPORTER_H
#define AVR_PERFORMANCEREPORTER_H


#include "../system/StaticTask.h"

class PerformanceReporter: public StaticTask<64> {
public:
    [[noreturn]] void run() override;
    void send();
    uint16_t executions = 0;
};


#endif //AVR_PERFORMANCEREPORTER_H
