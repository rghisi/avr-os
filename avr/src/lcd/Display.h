//
// Created by ghisi on 17.10.22.
//

#ifndef AVR_DISPLAY_H
#define AVR_DISPLAY_H

#include "../system/EventHandler.h"

class Display: public EventHandler {
public:
    Display();
    bool handle(Message* event) override;
    void clear();
    void text(uint8_t x, uint8_t y, char *text);
    void enableCursor(uint8_t x, uint8_t y);
    void disableCursor();
private:
    void drawCursor() const;
    bool cursorEnabled = false;
    uint8_t cursorX = 0;
    uint8_t cursorY = 0;
    static constexpr MessageType messageTypes[1] = {DISPLAY_COMMAND};
    static constexpr uint8_t messageTypeCount = 1;
};


#endif //AVR_DISPLAY_H
