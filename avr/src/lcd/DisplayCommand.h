//
// Created by ghisi on 12/31/22.
//

#ifndef AVR_DISPLAYCOMMAND_H
#define AVR_DISPLAYCOMMAND_H


#include "../system/Message.h"
#include "Command.h"

class DisplayCommand: public Message {
public:
    explicit DisplayCommand(Command* command);
    ~DisplayCommand() override;
    Command *command;
    static DisplayCommand* drawText(uint8_t x, uint8_t y, char* text);
    static DisplayCommand* enableCursor(uint8_t x, uint8_t y);
};


#endif //AVR_DISPLAYCOMMAND_H
