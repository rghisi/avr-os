//
// Created by ghisi on 03.11.23.
//

#ifndef AVR_PITASK_H
#define AVR_PITASK_H


#include "../system/StaticTask.h"

class PiTask: public StaticTask<128> {
    void run() override;
    double pi;
    double npi;
private:
    double n;
    double sign;
    uint32_t nn;
};


#endif //AVR_PITASK_H
