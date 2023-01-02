//
// Created by ghisi on 1/2/23.
//

#include "ClimateControl.h"

ClimateControl::ClimateControl(bool enabled, uint8_t temperature, uint8_t humidity): Message(MessageType::CLIMATE_CONTROL) {
    this->enabled = enabled;
    this->temperature = temperature;
    this->humidity = humidity;
}

ClimateControl::~ClimateControl() = default;
