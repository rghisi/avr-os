//
// Created by ghisi on 17.10.22.
//

#include "Display.h"
#include "../system/CpuStats.h"
#include "../system/MemoryStats.h"
#include "cstdio"
#include "../input/KeyPad.h"

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

EventType Display::type() {
    return CPU_STATS_DISPATCHED;
}

bool Display::handle(std::unique_ptr<Event> event) {
    switch (event->type()) {
        case CPU_STATS_DISPATCHED:
            stats(std::move(event));
            break;
        case SHOW_TEXT_REQUESTED:
            text(std::move(event));
            break;
        case MEMORY_STATS_DISPATCHED:
            memory(std::move(event));
            break;
        case KEYPAD_KEY_DOWN:
            keypad(std::move(event));
            break;
        default:
            break;
    }
    return true;
}

void Display::stats(std::unique_ptr<Event> event) {
    auto cpuStats = static_cast<CpuStats*>(event->data());
    char s[4];
    s[0] = ' ';
    s[1] = ' ';
    s[2] = ' ';
    s[3] = 0x00;
    LCD_PrintString(s);
    sprintf(s, "%" SCNu8, cpuStats->idlePercent());
    LCD_GotoXY(5, 0);
    LCD_PrintString(s);
}

void Display::text(std::unique_ptr<Event> event) {
    auto text = static_cast<char*>(event->data());
    LCD_GotoXY(0, 1);
    LCD_PrintString(text);
}

void Display::memory(std::unique_ptr<Event> event) {
    auto *memoryStats = static_cast<MemoryStats*>(event->data());
    char s[5];
    sprintf(s, "%" SCNu32, memoryStats->value);
    LCD_GotoXY(0, 0);
    LCD_PrintString(s);
}

void Display::keypad(std::unique_ptr<Event> event) {
    auto key = static_cast<KeyPad::Key*>(event->data());
    char s[2];
    s[1] = 0x00;
    switch (*(key)) {
        case KeyPad::Key::IDLE:
            s[0] = ' ';
            break;
        case KeyPad::Key::UP:
            s[0] = 'U';
            break;
        case KeyPad::Key::DOWN:
            s[0] = 'D';
            break;
        case KeyPad::Key::LEFT:
            s[0] = 'L';
            break;
        case KeyPad::Key::RIGHT:
            s[0] = 'R';
            break;
        case KeyPad::Key::CENTER:
            s[0] = 'C';
            break;
    }
    LCD_GotoXY(5, 1);
    LCD_PrintString(s);
}
