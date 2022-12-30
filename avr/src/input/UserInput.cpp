//
// Created by ghisi on 12.12.22.
//
#include "UserInput.h"

UserInput::UserInput(UserInput::Event event, uint16_t value) {
    this->event = event;
    this->value = value;
}
