//
// Created by ghisi on 10.11.22.
//

#ifndef AVR_CLIMATEREPORT_H
#define AVR_CLIMATEREPORT_H

#include "cstdint"
#include "../system/Message.h"

class ClimateReport: public Message {
public:
    ClimateReport(int32_t temperatureCelsius, uint32_t pressureMilliBar, uint32_t relativeHumidity);
    ~ClimateReport() override = default;
    int32_t temperatureCelsius;
    uint32_t pressureMilliBar;
    uint32_t relativeHumidity;
};


#endif //AVR_CLIMATEREPORT_H
