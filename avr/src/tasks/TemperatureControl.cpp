//
// Created by ghisi on 06.12.22.
//

#include "TemperatureControl.h"
#include "TemperatureControlCommand.h"
#include "TemperatureControlStatus.h"

TemperatureControl::TemperatureControl(Messaging *messaging, Dimmer *dimmer) {
    this->messaging = messaging;
    this->dimmer = dimmer;
}

void TemperatureControl::run() {
    if (enabled) {
        auto position = pid.update(temperatureSetPoint, currentTemperature);
        if (position < 0) {
            position = 0;
        }
        dimmer->setPosition(position);
        dimmer->enable();
    } else {
        dimmer->disable();
        pid.reset();
    }
    messaging->send(new TemperatureControlStatus(enabled, dimmer->getPosition()));
}

uint32_t TemperatureControl::delay() {
    return 1000;
}

Task::Type TemperatureControl::type() {
    return Type::PERIODIC;
}

void TemperatureControl::handle(Message* event) {
    switch (event->type()) {
        case CLIMATE_REPORT:
            handle(static_cast<ClimateReport *>(event));
            break;
        case TEMPERATURE_CONTROL_COMMAND:
            handle(static_cast<TemperatureControlCommand*>(event));
            break;
        default:
            break;
    }
}

void TemperatureControl::handle(ClimateReport *climateReport) {
    currentTemperature = (climateReport->temperatureCelsius);
}

void TemperatureControl::handle(TemperatureControlCommand *climateControl) {
    enabled = climateControl->enabled;
    temperatureSetPoint = (climateControl->temperature * 100) + 50;
}