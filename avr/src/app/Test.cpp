//
// Created by ghisi on 12.12.22.
//

#include "Test.h"
#include "../input/UserInput.h"
#include "cstdio"
#include "../lcd/DrawText.h"
#include "../lcd/DisplayCommand.h"

MessageType Test::eventType() {
    return USER_INPUT;
}

Test::Test(MessageDispatcher *eventDispatcher, Dimmer *dimmer) {
    this->eventDispatcher = eventDispatcher;
    this->dimmer = dimmer;
}

bool Test::handle(Message* event) {
    auto userInput = static_cast<UserInput*>(event);
    switch (userInput->event) {
        case UserInput::UserInputEvent::DIAL_PLUS:
            plus();
            break;
        case UserInput::UserInputEvent::DIAL_MINUS:
            minus();
            break;
        default:
            break;
    }
    return true;
}

void Test::plus() {
    dial++;
    dimmer->setPosition(dial);
    auto s = new char[4];
    sprintf(s, "%" PRIu8, dial);
    auto event = DisplayCommand::drawText(5, 0, s);
    eventDispatcher->dispatch(event);
}

void Test::minus() {
    dial--;
    dimmer->setPosition(dial);
    auto s = new char[4];
    sprintf(s, "%" PRIu8, dial);
    auto event = DisplayCommand::drawText(5, 0, s);
    eventDispatcher->dispatch(event);
}
