//
// Created by ghisi on 03.11.23.
//

#ifndef AVR_PITASK_H
#define AVR_PITASK_H


#include "../system/Task.h"

class PiTask: public Task {
    void run() override;
    double pi;
private:
    double n;
    double sign;
    uint32_t nn;
};


#endif //AVR_PITASK_H
