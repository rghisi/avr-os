//
// Created by ghisi on 10.11.22.
//

#include "BME280Report.h"

BME280Report::BME280Report(int32_t temperatureCelsius, uint32_t pressureMilliBar, uint32_t relativeHumidity)
: Message(MessageType::BME280_REPORT) {
    this->temperatureCelsius = temperatureCelsius;
    this->pressureMilliBar = pressureMilliBar;
    this->relativeHumidity = relativeHumidity;
}
