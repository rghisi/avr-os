//
// Created by ghisi on 19.03.23.
//

#ifndef AVR_PERFORMANCEREPORTER_H
#define AVR_PERFORMANCEREPORTER_H


#include "../system/Task.h"

class PerformanceReporter: public Task {
public:
    [[noreturn]] void run() override;
    void send() const;
    uint16_t executions = 0;
};


#endif //AVR_PERFORMANCEREPORTER_H
