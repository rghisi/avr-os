#ifndef HD44780_H_INCLUDED
#define HD44780_H_INCLUDED
/*
||
||  Filename:	 		HD44780.h
||  Title: 			    HD44780 Driver
||  Author: 			Efthymios Koktsidis
||	Email:				efthymios.ks@gmail.com
||  Compiler:		 	AVR-GCC
||	Description:
||	This library can drive HD44780 based LCD.
||	The LCD is driven exclusively in 4-bit mode.
||
*/

//----- Headers ------------//
#include <inttypes.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "IO_Macros.h"
#include "HD44780_Settings.h"
//--------------------------//

//----- Auxiliary data ---------------------------//
#define __LCD_Pulse_us                    1
#define __LCD_Delay_1                    20
#define __LCD_Delay_2                    10
#define __LCD_Delay_3                    1
#define __LCD_Delay_4                    1

#define __LCD_BusyFlag                    7

typedef struct {
    uint8_t X, Y;
} Point_t;

class HD44780 {
public:
    struct Config {
        uint8_t rows;
        uint8_t columns;
        uint8_t lineStarts[4];
    };
    enum class Command : uint8_t {
        ClearDisplay = 0x01,
        ReturnHome = 0x02,
        EntryModeSet = 0x04,
        DisplayControl = 0x08,
        CursorShift = 0x10,
        FunctionSet = 0x20,
        SetCGRAMAddress = 0x40,
        SetDDRAMAddress = 0x80,
        EntryIncrement = 0x02,
        EntryDecrement = 0x00,
        EntryShift = 0x01,
        EntryNoShift = 0x00,
        DisplayOn = 0x04,
        DisplayOff = 0x00,
        CursonOn = 0x02,
        CursorOff = 0x00,
        BlinkOn = 0x01,
        BlinkOff = 0x00,
        DisplayMove = 0x08,
        CursorMove = 0x00,
        MoveRight = 0x04,
        MoveLeft = 0x00,
        Mode8Bit = 0x10,
        Mode4Bit = 0x00,
        TwoLines = 0x08,
        OneLine = 0x00,
        FiveByTenDots = 0x04,
        FiveBy8Dots = 0x00
    };

    explicit HD44780(Config config);
    void setup();
    template<typename C, typename... T>
    void sendCommand(C command, T... commands);
    void sendData(char Character);
    void waitBusy();
    void buildChar(char *Data, uint8_t Position);
    void buildChar_P(const char *Data, uint8_t Position);
    void clear();
    void clearLine(uint8_t Line);
    void gotoXY(uint8_t X, uint8_t Y);
    Point_t getP();
    void printChar(char Character);
    void printString(char *Text);
    void printString_P(const char *Text);
    void printInteger(int32_t Value);
    void printDouble(double Value, uint32_t Tens);
    template<typename C, typename... T>
    void sendCommandHigh(C command, T... commands);
    void send(uint8_t Data);
    uint8_t read();
    void pulseEn();
    void Int2bcd(int32_t Value, char *BCD);

    constexpr static const Config EIGHT_BY_ONE = Config{.rows = 1, .columns = 8, .lineStarts = {0x00}};
    constexpr static const Config EIGHT_BY_TWO = Config{.rows = 2, .columns = 8, .lineStarts = {0x00, 0x40}};
    constexpr static const Config SIXTEEN_BY_ONE = Config{.rows = 1, .columns = 16, .lineStarts = {0x00}};
    constexpr static const Config SIXTEEN_BY_TWO = Config{.rows = 2, .columns = 16, .lineStarts = {0x00, 0x40}};
private:
    Config config;

    template<typename C, typename... T>
    uint8_t composeCommands(C command, T... commands);
    template<typename C>
    uint8_t composeCommands(C command);
};

#endif