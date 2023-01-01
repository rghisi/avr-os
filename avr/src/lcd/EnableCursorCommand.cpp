//
// Created by ghisi on 12/31/22.
//

#include "EnableCursorCommand.h"

EnableCursorCommand::EnableCursorCommand(uint8_t x, uint8_t y): Command(Type::ENABLE_CURSOR) {
    this->x = x;
    this->y = y;
}

EnableCursorCommand::~EnableCursorCommand() = default;
