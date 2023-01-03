//
// Created by ghisi on 17.10.22.
//

#include "Display.h"
#include "../system/CpuStats.h"
#include "cstdio"
#include "DisplayCommand.h"

extern "C" {
#include "one/HD44780.h"
}

Display::Display() {
    LCD_Setup();
    LCD_Clear();
    char hello[] = "Starting";
    LCD_PrintString(hello);
    _delay_ms(500);
    LCD_Clear();
}

void Display::handle(Message *event) {
    auto command = static_cast<DisplayCommand*>(event);
    command->command(this);
}

void Display::enableCursor(uint8_t x, uint8_t y) {
    cursorEnabled = true;
    cursorX = x;
    cursorY = y;
    drawCursor();
}

void Display::drawCursor() const {
    if (cursorEnabled) {
        LCD_GotoXY(cursorX, cursorY);
        LCD_SendCommand(
                __LCD_CMD_DisplayControl |
                __LCD_CMD_DisplayOn |
                __LCD_CMD_CursorOn
        );
    } else {
        LCD_SendCommand(
                __LCD_CMD_DisplayControl |
                __LCD_CMD_DisplayOn |
                __LCD_CMD_CursorOff
        );
    }
}

void Display::clear() {
    LCD_Clear();
}

void Display::text(uint8_t x, uint8_t y, char *text) {
    LCD_GotoXY(x, y);
    LCD_PrintString(text);
    drawCursor();
}

void Display::disableCursor() {
    cursorEnabled = false;
    drawCursor();
}
