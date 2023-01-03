//
// Created by ghisi on 12/31/22.
//

#ifndef AVR_ENABLECURSOR_H
#define AVR_ENABLECURSOR_H


#include "DisplayCommand.h"
#include "functional"

class EnableCursor: public DisplayCommand {
public:
    EnableCursor(uint8_t x, uint8_t y);
    ~EnableCursor() override;
    void command(Display *display) override;
private:
    uint8_t x;
    uint8_t y;
};


#endif //AVR_ENABLECURSOR_H
