//
// Created by ghisi on 10.11.22.
//

#include "ClimateReport.h"

ClimateReport::ClimateReport(int32_t temperatureCelsius, uint32_t pressureMilliBar, uint32_t relativeHumidity)
: Message(MessageType::CLIMATE_REPORT) {
    this->temperatureCelsius = temperatureCelsius;
    this->pressureMilliBar = pressureMilliBar;
    this->relativeHumidity = relativeHumidity;
}
