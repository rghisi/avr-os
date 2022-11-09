#include "HD44780.h"
#include "cstdarg"

HD44780::HD44780(HD44780::Config config) {
    this->config = config;
}

void HD44780::setup() {
    //LCD pins = Outputs
    PinMode(LCD_D4, Output);
    PinMode(LCD_D5, Output);
    PinMode(LCD_D6, Output);
    PinMode(LCD_D7, Output);
    PinMode(LCD_RS, Output);
    PinMode(LCD_RW, Output);
    PinMode(LCD_EN, Output);

    //LCD pins = 0
    DigitalWrite(LCD_D4, Low);
    DigitalWrite(LCD_D5, Low);
    DigitalWrite(LCD_D6, Low);
    DigitalWrite(LCD_D7, Low);
    DigitalWrite(LCD_RS, Low);
    DigitalWrite(LCD_RW, Low);
    DigitalWrite(LCD_EN, Low);

    //----- Soft reset -----
    //1. Wait for more than 15ms
    _delay_ms(__LCD_Delay_1);
    //2. Command 32: LCD 8-bit mode
    sendCommandHigh(Command::FunctionSet, Command::Mode8Bit);
    //3. Wait for more than 4.1ms
    _delay_ms(__LCD_Delay_2);
    //4. Command 32: LCD 8-bit mode
    sendCommandHigh(Command::FunctionSet, Command::Mode8Bit);
    //5. Wait for more than 100us
    _delay_ms(__LCD_Delay_3);
    //6. Command 32: LCD 8-bit mode, for the 3rd time
    sendCommandHigh(Command::FunctionSet, Command::Mode8Bit);
    //7. Wait for more than 100us
    _delay_ms(__LCD_Delay_4);

    //----- Initialization -----
    //1. Command 32: LCD mode
    sendCommandHigh(Command::FunctionSet, Command::Mode4Bit);
    //2. Command 32: LCD mode and size
    sendCommand(Command::FunctionSet,  Command::Mode4Bit,  Command::TwoLines, Command::FiveBy8Dots);
    //3. Command 8: Display On, Cursor off, Blinking Off
    sendCommand(Command::DisplayControl, Command::DisplayOn, Command::CursorOff, Command::BlinkOff);
    //4. Command 4: Auto increment, No shifting
    sendCommand(Command::EntryModeSet, Command::EntryIncrement, Command::EntryNoShift);
    //5. Command 1: Clear display, cursor at home
    sendCommand(Command::ClearDisplay);
}

template<typename C, typename... T>
void HD44780::sendCommand(C command, T... commands) {
    waitBusy();

    DigitalWrite(LCD_RS, Low);
    send(composeCommands(command, commands...));
}

//Send data to LCD.
void HD44780::sendData(char c) {
    waitBusy();

    DigitalWrite(LCD_RS, High);
    send((uint8_t) (c));
}

//Wait until busy flag is cleared.
void HD44780::waitBusy() {
    uint8_t busy = 0;

    PinMode(LCD_D4, Input);                //D7:D4 = Inputs
    PinMode(LCD_D5, Input);
    PinMode(LCD_D6, Input);
    PinMode(LCD_D7, Input);
    DigitalWrite(LCD_RS, Low);            //RS=0
    DigitalWrite(LCD_RW, High);            //RW=1

    do {
        //High nibble comes first
        DigitalWrite(LCD_EN, High);
        _delay_us(__LCD_Pulse_us);
        busy &= ~(1 << __LCD_BusyFlag);
        busy |= (DigitalRead(LCD_D7) << __LCD_BusyFlag);
        DigitalWrite(LCD_EN, Low);

        //Low nibble follows
        pulseEn();
    } while (BitCheck(busy, __LCD_BusyFlag));

    PinMode(LCD_D4, Output);            //D7:D4 = Outputs
    PinMode(LCD_D5, Output);
    PinMode(LCD_D6, Output);
    PinMode(LCD_D7, Output);
    DigitalWrite(LCD_RW, Low);            //RW = 0
}

//Build character in LCD CGRAM from data in SRAM.
void HD44780::buildChar(char *Data, uint8_t Position) {
    if (Position < 0)
        return;
    if (Position >= 8)
        return;

    Point_t p = getP();
    uint8_t i;

    //Every character in CGRAM needs 8bytes
    //this will fail?
    sendCommand(Command::SetCGRAMAddress, (Position << 3));

    //Save the character byte-by-byte
    for (i = 0; i < 8; i++)
        sendData(Data[i]);

    //Return to the DDRAM position
    gotoXY(p.X, p.Y);
}

//Build character in LCD CGRAM from data in Flash memory.
void HD44780::buildChar_P(const char *Data, uint8_t Position) {
    if (Position < 0)
        return;
    if (Position >= 8)
        return;

    Point_t p = getP();
    uint8_t i;

    //Every character in CGRAM needs 8bytes
    //this will fail?
    sendCommand(Command::SetCGRAMAddress, Position << 3);

    //Save the character byte-by-byte
    for (i = 0; i < 8; i++)
        sendData(pgm_read_byte(Data[i]));

    //Return to the DDRAM position
    gotoXY(p.X, p.Y);
}

//Clear display.
void HD44780::clear() {
    sendCommand(Command::ClearDisplay);
}

//Clear line.
void HD44780::clearLine(uint8_t Line) {
    uint8_t i = 0;

    gotoXY(0, Line);
    while (i <= config.columns) {
        sendData(' ');
        i++;
    }
}

//Go to specified position.
void HD44780::gotoXY(uint8_t X, uint8_t Y) {
    if ((X < config.columns) && (Y < config.rows)) {
        uint8_t addr = 0;
        switch (Y) {
            case (0):
                addr = config.lineStarts[0];
                break;
            case (1):
                addr = config.lineStarts[1];
                break;
            case (2):
                addr = config.lineStarts[2];
                break;
            case (3):
                addr = config.lineStarts[3];
                break;
        }
        //this will fail?
        sendCommand(Command::SetDDRAMAddress, (addr | X));
    }
}

//Get current position.
Point_t HD44780::getP() {
    Point_t p;
    p.X = read();
    p.Y = 0;
    if (config.rows == 2 && p.X >= config.lineStarts[1]) {
        p.X -= config.lineStarts[1];
        p.Y = 1;
    }
    return p;
}

//Print character.
void HD44780::printChar(char Character) {
    sendData(Character);
}

//Print string from SRAM.
void HD44780::printString(char *Text) {
    while (*Text)
        sendData(*Text++);
}

//Print string from Flash memory.
void HD44780::printString_P(const char *Text) {
    char r = pgm_read_byte(Text++);
    while (r) {
        sendData(r);
        r = pgm_read_byte(Text++);
    }
}

//Print integer.
void HD44780::printInteger(int32_t Value) {
    if (Value == 0) {
        printChar('0');
    } else if ((Value > INT32_MIN) && (Value <= INT32_MAX)) {
        //int32_max + sign + null = 12 bytes
        char arr[12] = {'\0'};

        //Convert integer to array (returns in reversed order)
        Int2bcd(Value, arr);

        //Print
        printString(arr);
    }
}

//Print double.
void HD44780::printDouble(double Value, uint32_t Tens) {
    if (Value == 0) {
        //Print characters individually so no string is stored into RAM.
        printChar('0');
        printChar('.');
        printChar('0');
    } else if ((Value >= (-2147483647)) && (Value < 2147483648)) {
        //Print sign
        if (Value < 0) {
            Value = -Value;
            printChar('-');
        }

        //Print integer part
        printInteger(Value);

        //Print dot
        printChar('.');

        //Print decimal part
        printInteger((Value - (uint32_t) (Value)) * Tens);
    }
}

template<typename C, typename... T>
uint8_t HD44780::composeCommands(C command, T... commands) {
    return ((uint8_t)command) | composeCommands(commands...);
}

template<typename C>
uint8_t HD44780::composeCommands(C command) {
    return ((uint8_t)command);
}

template<typename C, typename... T>
void HD44780::sendCommandHigh(C command, T... commands) {
    uint8_t c = composeCommands(command, commands...);

    DigitalWrite(LCD_RS, Low);

    //Send the high nibble
    DigitalWrite(LCD_D4, BitCheck(c, 4));
    DigitalWrite(LCD_D5, BitCheck(c, 5));
    DigitalWrite(LCD_D6, BitCheck(c, 6));
    DigitalWrite(LCD_D7, BitCheck(c, 7));
    pulseEn();
}

//Send data to LCD.
void HD44780::send(uint8_t Data) {
    //Send the high nibble
    DigitalWrite(LCD_D4, BitCheck(Data, 4));
    DigitalWrite(LCD_D5, BitCheck(Data, 5));
    DigitalWrite(LCD_D6, BitCheck(Data, 6));
    DigitalWrite(LCD_D7, BitCheck(Data, 7));
    pulseEn();

    //Low nibble comes after
    DigitalWrite(LCD_D4, BitCheck(Data, 0));
    DigitalWrite(LCD_D5, BitCheck(Data, 1));
    DigitalWrite(LCD_D6, BitCheck(Data, 2));
    DigitalWrite(LCD_D7, BitCheck(Data, 3));
    pulseEn();
}

//Read status from LCD.
uint8_t HD44780::read() {
    uint8_t status = 0;

    waitBusy();

    PinMode(LCD_D4, Input);                //D7:D4 = Inputs
    PinMode(LCD_D5, Input);
    PinMode(LCD_D6, Input);
    PinMode(LCD_D7, Input);
    DigitalWrite(LCD_RS, Low);            //RS = 0
    DigitalWrite(LCD_RW, High);            //RW = 1

    //High nibble comes first
    DigitalWrite(LCD_EN, High);
    _delay_us(__LCD_Pulse_us);
    status |= DigitalRead(LCD_D4) << 4;
    status |= DigitalRead(LCD_D5) << 5;
    status |= DigitalRead(LCD_D6) << 6;
    DigitalWrite(LCD_EN, Low);

    //Low nibble follows
    DigitalWrite(LCD_EN, High);
    _delay_us(__LCD_Pulse_us);
    status |= DigitalRead(LCD_D4);
    status |= DigitalRead(LCD_D5) << 1;
    status |= DigitalRead(LCD_D6) << 2;
    status |= DigitalRead(LCD_D7) << 3;
    DigitalWrite(LCD_EN, Low);

    PinMode(LCD_D4, Output);            //D7:D4 = Outputs
    PinMode(LCD_D5, Output);
    PinMode(LCD_D6, Output);
    PinMode(LCD_D7, Output);
    DigitalWrite(LCD_RW, Low);            //RW = 0

    return status;
}

//Sends pulse to PIN_EN of LCD.
inline void HD44780::pulseEn() {
    DigitalWrite(LCD_EN, High);
//    _delay_us(__LCD_Pulse_us);
    DigitalWrite(LCD_EN, Low);
}

//Converts integer value to BCD.
void HD44780::Int2bcd(int32_t Value, char BCD[]) {
    uint8_t isNegative = 0;

    BCD[0] = BCD[1] = BCD[2] =
    BCD[3] = BCD[4] = BCD[5] =
    BCD[6] = BCD[7] = BCD[8] =
    BCD[9] = BCD[10] = '0';

    if (Value < 0) {
        isNegative = 1;
        Value = -Value;
    }

    while (Value > 1000000000) {
        Value -= 1000000000;
        BCD[1]++;
    }

    while (Value >= 100000000) {
        Value -= 100000000;
        BCD[2]++;
    }

    while (Value >= 10000000) {
        Value -= 10000000;
        BCD[3]++;
    }

    while (Value >= 1000000) {
        Value -= 1000000;
        BCD[4]++;
    }

    while (Value >= 100000) {
        Value -= 100000;
        BCD[5]++;
    }

    while (Value >= 10000) {
        Value -= 10000;
        BCD[6]++;
    }

    while (Value >= 1000) {
        Value -= 1000;
        BCD[7]++;
    }

    while (Value >= 100) {
        Value -= 100;
        BCD[8]++;
    }

    while (Value >= 10) {
        Value -= 10;
        BCD[9]++;
    }

    while (Value >= 1) {
        Value -= 1;
        BCD[10]++;
    }

    uint8_t i = 0;
    //Find first non zero digit
    while (BCD[i] == '0')
        i++;

    //Add sign
    if (isNegative) {
        i--;
        BCD[i] = '-';
    }

    //Shift array
    uint8_t end = 10 - i;
    uint8_t offset = i;
    i = 0;
    while (i <= end) {
        BCD[i] = BCD[i + offset];
        i++;
    }
    BCD[i] = '\0';
}
