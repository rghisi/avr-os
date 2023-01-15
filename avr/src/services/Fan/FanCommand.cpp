//
// Created by ghisi on 1/10/23.
//

#include "FanCommand.h"

FanCommand::FanCommand(uint8_t power): Message(MessageType::FAN_COMMAND) {
    this->power = power;
}
