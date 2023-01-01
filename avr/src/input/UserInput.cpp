//
// Created by ghisi on 12.12.22.
//
#include "UserInput.h"

UserInput::UserInput(UserInput::UserInputEvent event, uint16_t value) : Message(MessageType::USER_INPUT) {
    this->event = event;
    this->value = value;
}