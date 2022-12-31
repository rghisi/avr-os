//
// Created by ghisi on 14.11.22.
//

#include "TempHumControl.h"

void TempHumControl::run() {
    temperatureOutput = temperaturePid.update(setTemperature, temperatureOutput);
    humidityOutput = humidityPid.update(setHumidity, humidityOutput);
    
}

uint32_t TempHumControl::delay() {
    return 1000;
}

Task::Type TempHumControl::type() {
    return Type::PERIODIC;
}

bool TempHumControl::handle(Event* event) {
    switch (event->type()) {
        case BME280_REPORT:
            break;
        default:
            break;
    }
    return false;
}

EventType TempHumControl::eventType() {
    return BME280_REPORT;
}
