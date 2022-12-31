//
// Created by ghisi on 10.11.22.
//

#ifndef AVR_BME280REPORT_H
#define AVR_BME280REPORT_H


#include "cstdint"
#include "../system/Event.h"

class BME280Report: public Event {
public:
    BME280Report(int32_t temperatureCelsius, uint32_t pressureMilliBar, uint32_t relativeHumidity);
    ~BME280Report() override = default;
    int32_t temperatureCelsius;
    uint32_t pressureMilliBar;
    uint32_t relativeHumidity;
};


#endif //AVR_BME280REPORT_H
