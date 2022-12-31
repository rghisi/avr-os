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

bool Display::handle(Event* event) {
    switch (event->type()) {
        case CPU_STATS_READ:
            stats(event);
            break;
        case SHOW_TEXT_REQUESTED:
            text(event);
            break;
        case MEMORY_STATS_READ:
            memory(event);
            break;
        case USER_INPUT:
            input(event);
            break;
        case SENSOR_READ:
            sensor(event);
        default:
            break;
    }
    return true;
}

void Display::stats(Event* event) {
    auto cpuStats = static_cast<CpuStats*>(event->data());
    char s[4];
    s[0] = ' ';
    s[1] = ' ';
    s[2] = ' ';
    s[3] = 0x00;
    LCD_PrintString(s);
    sprintf(s, "%" PRIu8, cpuStats->idlePercent());
    LCD_GotoXY(13, 0);
    LCD_PrintString(s);
}

void Display::text(Event* event) {
    auto text = static_cast<char*>(event->data());
    LCD_GotoXY(0, 1);
    LCD_PrintString(text);
}

void Display::memory(Event* event) {
    auto *memoryStats = static_cast<MemoryStats*>(event->data());
    char s[5];
    sprintf(s, "%" PRIu32, memoryStats->value);
    LCD_GotoXY(0, 0);
    LCD_PrintString(s);
}

void Display::input(Event* event) {
    auto userInput = static_cast<UserInput*>(event->data());
    char s[8];
    sprintf(s, "       ");
    LCD_GotoXY(5, 0);
    LCD_PrintString(s);
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
        case UserInput::Event::BUTTON_LEFT_PRESSED:
            sprintf(s, "LP");
            break;
        case UserInput::Event::BUTTON_LEFT_RELEASED:
            sprintf(s, "LR");
            break;
        case UserInput::Event::BUTTON_UP_PRESSED:
            sprintf(s, "UP");
            break;
        case UserInput::Event::BUTTON_UP_RELEASED:
            sprintf(s, "UR");
            break;
        case UserInput::Event::BUTTON_RIGHT_PRESSED:
            sprintf(s, "RP");
            break;
        case UserInput::Event::BUTTON_RIGHT_RELEASED:
            sprintf(s, "RR");
            break;
        case UserInput::Event::BUTTON_DOWN_PRESSED:
            sprintf(s, "DP");
            break;
        case UserInput::Event::BUTTON_DOWN_RELEASED:
            sprintf(s, "DR");
            break;
        case UserInput::Event::BUTTON_ENTER_PRESSED:
            sprintf(s, "EP");
            break;
        case UserInput::Event::BUTTON_ENTER_RELEASED:
            sprintf(s, "ER");
            break;
        default:
            sprintf(s, "%" PRIu16, userInput->value);
            break;
    }
    LCD_GotoXY(5, 0);
    LCD_PrintString(s);
}

void Display::sensor(Event* event) {
    auto *bme280Report = static_cast<BME280Report*>(event->data());
    char s[12];
    sprintf(s, "%" PRId32 " %" PRIu32, bme280Report->temperatureCelsius, bme280Report->relativeHumidity);
    LCD_GotoXY(6, 1);
    LCD_PrintString(s);
}
