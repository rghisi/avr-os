//
// Created by ghisi on 1/3/23.
//

#include "TemperatureControlStatus.h"

TemperatureControlStatus::~TemperatureControlStatus() = default;

TemperatureControlStatus::TemperatureControlStatus(bool enabled, uint16_t position)
: Message(MessageType::TEMPERATURE_CONTROL_STATUS) {
    this->enabled = enabled;
    this->position = position;
}
