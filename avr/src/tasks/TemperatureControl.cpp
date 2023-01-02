//
// Created by ghisi on 06.12.22.
//

#include "TemperatureControl.h"
#include "../sensors/ClimateReport.h"
#include "ClimateControl.h"

TemperatureControl::TemperatureControl(Messaging *messageDispatcher, Dimmer *dimmer) {
    this->messageDispatcher = messageDispatcher;
    this->dimmer = dimmer;
}

void TemperatureControl::run() {
    if (enabled) {
        dimmerPosition = pid.update(temperatureSetPoint, currentTemperature);
        if (dimmerPosition > 255) {
            dimmer->setPosition(255);
        } else if (dimmerPosition < 0) {
            dimmer->setPosition(0);
        } else {
            dimmer->setPosition((uint8_t)dimmerPosition);
        }
        dimmer->enable();
    } else {
        dimmer->disable();
    }
}

uint32_t TemperatureControl::delay() {
    return 1000;
}

Task::Type TemperatureControl::type() {
    return Type::PERIODIC;
}

bool TemperatureControl::handle(Message* event) {
    switch (event->type()) {
        case CLIMATE_REPORT:
            handle(static_cast<ClimateReport *>(event));
            break;
        case CLIMATE_CONTROL:
            handle(static_cast<ClimateControl*>(event));
            break;
        default:
            break;
    }
    return true;
}

void TemperatureControl::handle(ClimateReport *climateReport) {
    currentTemperature = (climateReport->temperatureCelsius);
}

void TemperatureControl::handle(ClimateControl *climateControl) {
    enabled = climateControl->enabled;
    temperatureSetPoint = climateControl->temperature;
}