//
// Created by ghisi on 12/31/22.
//

#ifndef AVR_ENABLECURSORCOMMAND_H
#define AVR_ENABLECURSORCOMMAND_H


#include "../system/Message.h"
#include "Command.h"

class EnableCursorCommand: public Command {
public:
    EnableCursorCommand(uint8_t x, uint8_t y);
    ~EnableCursorCommand() override;
    uint8_t x;
    uint8_t y;
};


#endif //AVR_ENABLECURSORCOMMAND_H
