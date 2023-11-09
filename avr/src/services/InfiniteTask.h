//
// Created by ghisi on 11.03.23.
//

#ifndef AVR_INFINITETASK_H
#define AVR_INFINITETASK_H


#include "../system/Task.h"
#include "../system/StaticTask.h"

class InfiniteTask: public StaticTask<64> {
public:
    explicit InfiniteTask(uint8_t taskNumber);
    void run() override;
private:
    uint8_t taskNumber;
    void print(uint16_t counter, uint8_t i);
    void printMessage(uint16_t counter, uint8_t i);
};


#endif //AVR_INFINITETASK_H
