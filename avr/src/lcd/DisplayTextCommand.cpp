//
// Created by ghisi on 12/31/22.
//

#include "DisplayTextCommand.h"

DisplayTextCommand::DisplayTextCommand(char *text)
        : Event(EventType::SHOW_TEXT_REQUESTED) {
    this->text = text;
}

DisplayTextCommand::~DisplayTextCommand() {
    delete text;
}
