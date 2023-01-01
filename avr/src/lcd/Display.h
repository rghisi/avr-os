//
// Created by ghisi on 17.10.22.
//

#ifndef AVR_DISPLAY_H
#define AVR_DISPLAY_H


#include "../system/EventHandler.h"
#include "DrawText.h"
#include "EnableCursorCommand.h"

class Display: public EventHandler {
public:
    Display();
    MessageType eventType() override;
    bool handle(Message* event) override;

private:
    void text(DrawText* command);
    void enableCursor(EnableCursorCommand *command);
    void drawCursor() const;
    bool cursorEnabled = false;
    uint8_t cursorX = 0;
    uint8_t cursorY = 0;
};


#endif //AVR_DISPLAY_H
