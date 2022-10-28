//
// Created by ghisi on 17.10.22.
//

#include "Display.h"
#include "../system/CpuStats.h"
#include "../system/MemoryStats.h"
#include "cstdio"

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

bool Display::handle(Event *event) {
    switch (event->type()) {
        case CPU_STATS_DISPATCHED:
            stats(event);
            break;
        case SHOW_TEXT_REQUESTED:
            text(event);
            break;
        case MEMORY_STATS_DISPATCHED:
            memory(event);
            break;
        default:
            break;
    }
    return true;
}

void Display::stats(Event *event) {
    auto *cpuStats = static_cast<CpuStats*>(event->data());
    char s[4];
    sprintf(s, "%" SCNu8, cpuStats->idlePercent());
    LCD_GotoXY(5, 0);
    LCD_PrintString(s);
}

void Display::text(Event *event) {
    auto text = static_cast<char*>(event->data());
    LCD_GotoXY(0, 1);
    LCD_PrintString(text);
}

void Display::memory(Event *event) {
    auto *memoryStats = static_cast<MemoryStats*>(event->data());
    char s[5];
    sprintf(s, "%" SCNu32, memoryStats->value);
    LCD_GotoXY(0, 0);
    LCD_PrintString(s);
}


