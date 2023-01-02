//
// Created by ghisi on 12/31/22.
//

#ifndef AVR_ENABLECURSORCOMMAND_H
#define AVR_ENABLECURSORCOMMAND_H


#include "DisplayCommand.h"
#include "functional"

class EnableCursorCommand: public DisplayCommand {
public:
    EnableCursorCommand(uint8_t x, uint8_t y);
    ~EnableCursorCommand() override;
    void command(Display *display) override;
private:
    uint8_t x;
    uint8_t y;
};


#endif //AVR_ENABLECURSORCOMMAND_H
