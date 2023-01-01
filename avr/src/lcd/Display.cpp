//
// Created by ghisi on 17.10.22.
//

#include "Display.h"
#include "../system/CpuStats.h"
#include "cstdio"
#include "../sensors/BME280Report.h"
#include "../input/UserInput.h"
#include "DrawText.h"
#include "DisplayCommand.h"
#include "EnableCursorCommand.h"

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

MessageType Display::eventType() {
    return DISPLAY_COMMAND;
}

bool Display::handle(Message *event) {
    auto command = static_cast<DisplayCommand *>(event)->command;
    switch (command->type) {
        case Command::Type::DRAW_TEXT:
            text(static_cast<DrawText *>(command));
            break;
        case Command::Type::ENABLE_CURSOR:
            enableCursor(static_cast<EnableCursorCommand *>(command));
            break;
        case Command::Type::DISABLE_CURSOR:
            break;
    }
    return true;
}

void Display::text(DrawText *command) {
    LCD_GotoXY(command->x, command->y);
    LCD_PrintString(command->text);
    drawCursor();
}

void Display::enableCursor(EnableCursorCommand *command) {
    cursorEnabled = true;
    cursorX = command->x;
    cursorY = command->y;
    drawCursor();
}

void Display::drawCursor() const {
    if (cursorEnabled) {
        LCD_GotoXY(cursorX, cursorY);
        LCD_SendCommand(
                __LCD_CMD_DisplayControl |
                __LCD_CMD_DisplayOn |
                __LCD_CMD_CursorOn |
                __LCD_CMD_BlinkOn
        );
    } else {
        LCD_SendCommand(
                __LCD_CMD_DisplayControl |
                __LCD_CMD_DisplayOn |
                __LCD_CMD_CursorOff |
                __LCD_CMD_BlinkOff
        );
    }
}

//void Display::sensor(Message* event) {
//    auto *bme280Report = static_cast<BME280Report*>(event);
//    char s[12];
//    sprintf(s, "%" PRId32 " %" PRIu32, bme280Report->temperatureCelsius, bme280Report->relativeHumidity);
//    LCD_GotoXY(6, 1);
//    LCD_PrintString(s);
//}
