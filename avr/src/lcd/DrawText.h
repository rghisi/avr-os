//
// Created by ghisi on 12/31/22.
//

#ifndef AVR_DRAWTEXT_H
#define AVR_DRAWTEXT_H


#include "DisplayCommand.h"
#include "functional"

class DrawText: public DisplayCommand {
public:
    explicit DrawText(uint8_t x, uint8_t y, char *text);
    ~DrawText() override;
    void command(Display *display) override;
    char *text;
    uint8_t x;
    uint8_t y;
};


#endif //AVR_DRAWTEXT_H
