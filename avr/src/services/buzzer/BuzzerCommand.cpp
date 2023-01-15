//
// Created by ghisi on 1/10/23.
//

#include "BuzzerCommand.h"

BuzzerCommand::BuzzerCommand(uint8_t duration): Message(MessageType::BUZZER) {
    this->duration = duration;
}

BuzzerCommand::~BuzzerCommand() = default;
