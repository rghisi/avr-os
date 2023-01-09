//
// Created by ghisi on 1/2/23.
//

#include "TemperatureControlCommand.h"

TemperatureControlCommand::TemperatureControlCommand(bool enabled, uint8_t temperature, uint8_t humidity): Message(MessageType::TEMPERATURE_CONTROL_COMMAND) {
    this->enabled = enabled;
    this->temperature = temperature;
    this->humidity = humidity;
}

TemperatureControlCommand::~TemperatureControlCommand() = default;
