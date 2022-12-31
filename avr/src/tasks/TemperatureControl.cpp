//
// Created by ghisi on 06.12.22.
//

#include "TemperatureControl.h"
#include "../sensors/BME280Report.h"

TemperatureControl::TemperatureControl(Dimmer *dimmer) {
    this->dimmer = dimmer;
}

void TemperatureControl::run() {
    dimmerPosition = pid.update(temperatureSetPoint, currentTemperature);
    if (dimmerPosition > 255) {
        dimmer->setPosition(255);
    } else if (dimmerPosition < 0) {
        dimmer->setPosition(0);
    } else {
        dimmer->setPosition((uint8_t)dimmerPosition);
    }
}

uint32_t TemperatureControl::delay() {
    return 1000;
}

Task::Type TemperatureControl::type() {
    return Type::PERIODIC;
}

EventType TemperatureControl::eventType() {
    return BME280_REPORT;
}

bool TemperatureControl::handle(Event* event) {
    auto bmeReport = static_cast<BME280Report*>(event);
    currentTemperature = (bmeReport->temperatureCelsius);
    return true;
}
