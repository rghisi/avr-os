//
// Created by ghisi on 12/30/22.
//

#ifndef AVR_TIMETICK_H
#define AVR_TIMETICK_H


#include "cstdint"
#include "../system/Message.h"

class TimeTick: public Message {
public:
    explicit TimeTick(uint32_t timestamp);
    ~TimeTick() override = default;
    uint32_t millis();
private:
    uint32_t timestamp;
};


#endif //AVR_TIMETICK_H
