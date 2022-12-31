//
// Created by ghisi on 12/30/22.
//

#ifndef AVR_TIMETICKDATA_H
#define AVR_TIMETICKDATA_H


#include "cstdint"

class TimeTickData {
public:
    explicit TimeTickData(uint32_t timestamp);
    uint32_t millis();
private:
    uint32_t timestamp;
};


#endif //AVR_TIMETICKDATA_H
