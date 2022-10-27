//
// Created by ghisi on 17.10.22.
//

#ifndef AVR_CPUSTATS_H
#define AVR_CPUSTATS_H


#include "cstdint"

class CpuStats {
public:
    void start(uint32_t startTimestamp);
    void end(uint32_t endTimestamp, bool usedNotIdle);
    uint8_t idlePercent();
    uint32_t usedTime = 0;
    uint32_t idleTime = 0;
private:
    uint32_t startTimestamp;
};


#endif //AVR_CPUSTATS_H
