//
// Created by ghisi on 17.10.22.
//

#ifndef AVR_CPUSTATS_H
#define AVR_CPUSTATS_H


#include "cstdint"

class CpuStats {
public:
    static uint16_t schedulerUserTime;
    static uint16_t eventLoopUserTime;
};


#endif //AVR_CPUSTATS_H
