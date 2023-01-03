//
// Created by ghisi on 12/31/22.
//

#include "EnableCursor.h"

EnableCursor::EnableCursor(uint8_t x, uint8_t y) {
    this->x = x;
    this->y = y;
}

EnableCursor::~EnableCursor() = default;

void EnableCursor::command(Display *display) {
    display->enableCursor(x, y);
}
