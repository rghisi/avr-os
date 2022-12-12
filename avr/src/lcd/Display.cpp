//
// Created by ghisi on 17.10.22.
//

#include "Display.h"
#include "../system/CpuStats.h"
#include "../system/MemoryStats.h"
#include "cstdio"
#include "../input/KeyPad.h"
#include "../sensors/BME280Report.h"
#include "../input/UserInput.h"

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

EventType Display::eventType() {
    return CPU_STATS_READ;
}

bool Display::handle(std::unique_ptr<Event> event) {
    switch (event->type()) {
        case CPU_STATS_READ:
            stats(std::move(event));
            break;
        case SHOW_TEXT_REQUESTED:
            text(std::move(event));
            break;
        case MEMORY_STATS_READ:
            memory(std::move(event));
            break;
        case USER_INPUT:
            input(std::move(event));
            break;
        case SENSOR_READ:
            sensor(std::move(event));
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
    LCD_GotoXY(13, 0);
    LCD_PrintString(s);
}

void Display::text(std::unique_ptr<Event> event) {
    auto text = static_cast<char*>(event->data());
    LCD_GotoXY(0, 1);
    LCD_PrintString(text);
    delete text;
}

void Display::memory(std::unique_ptr<Event> event) {
    auto *memoryStats = static_cast<MemoryStats*>(event->data());
    char s[5];
    sprintf(s, "%" SCNu32, memoryStats->value);
    LCD_GotoXY(0, 0);
    LCD_PrintString(s);
}

void Display::input(std::unique_ptr<Event> event) {
    auto userInput = static_cast<UserInput*>(event->data());
    char s[4];
    switch (userInput->event) {
        case UserInput::Event::DIAL_PLUS:
            dial++;
            sprintf(s, "%" PRIu8, dial);
            break;
        case UserInput::Event::DIAL_MINUS:
            dial--;
            sprintf(s, "%" PRIu8, dial);
            break;
        case UserInput::Event::DIAL_BUTTON_PRESSED:
            s[0] = 'P';
            break;
        case UserInput::Event::DIAL_BUTTON_RELEASED:
            s[0] = 'R';
            break;
        default:
            break;
    }
    delete userInput;
    LCD_GotoXY(11, 0);
    LCD_PrintString(s);
}

void Display::sensor(std::unique_ptr<Event> event) {
    auto *bme280Report = static_cast<BME280Report*>(event->data());
    char s[12];
    sprintf(s, "%" SCNi32 " %" SCNu32, bme280Report->temperatureCelsius, bme280Report->relativeHumidity);
    LCD_GotoXY(6, 1);
    LCD_PrintString(s);
    delete bme280Report;
}
