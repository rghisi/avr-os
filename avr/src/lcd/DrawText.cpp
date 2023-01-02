//
// Created by ghisi on 12/31/22.
//

#include "DrawText.h"

DrawText::DrawText(uint8_t x, uint8_t y, char *text) {
    this->x = x;
    this->y = y;
    this->text = text;
}

DrawText::~DrawText() {
    delete text;
}

void DrawText::command(Display *display) {
    display->text(x, y, text);
}
