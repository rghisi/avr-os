//
// Created by ghisi on 11.03.23.
//

#ifndef AVR_INFINITETASK_H
#define AVR_INFINITETASK_H


#include "../system/Task.h"
#include "../system/Messaging.h"

class InfiniteTask: public Task {
public:
    explicit InfiniteTask(uint8_t taskNumber);
    void run() override;
private:
    uint8_t taskNumber;
    void print(uint16_t counter) const;
    void printMessage(uint16_t counter) const;
};


#endif //AVR_INFINITETASK_H
