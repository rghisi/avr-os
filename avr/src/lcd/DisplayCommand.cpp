//
// Created by ghisi on 12/31/22.
//

#include "DisplayCommand.h"
#include "DrawText.h"
#include "EnableCursorCommand.h"

DisplayCommand::DisplayCommand(Command *command): Message(MessageType::DISPLAY_COMMAND) {
    this->command = command;
}

DisplayCommand::~DisplayCommand() {
    delete command;
}

DisplayCommand* DisplayCommand::drawText(uint8_t x, uint8_t y, char *text) {
    return new DisplayCommand(new DrawText(x, y, text));
}

DisplayCommand *DisplayCommand::enableCursor(uint8_t x, uint8_t y) {
    return new DisplayCommand(new EnableCursorCommand(x, y));
};
