//
// Created by ghisi on 17.10.22.
//

#ifndef AVR_DISPLAY_H
#define AVR_DISPLAY_H

#include "../system/Subscriber.h"

class Display: public Subscriber {
public:
    Display();
    void handle(Message* event) override;
    void clear();
    void text(uint8_t x, uint8_t y, char *text);
    void enableCursor(uint8_t x, uint8_t y);
    void disableCursor();
private:
    void drawCursor() const;
    bool cursorEnabled = false;
    uint8_t cursorX = 0;
    uint8_t cursorY = 0;
};


#endif //AVR_DISPLAY_H
