//
// Created by ghisi on 12.12.22.
//

#include "Test.h"
#include "../input/UserInput.h"
#include "cstdio"
#include "../lcd/DrawText.h"
#include "cstring"
#include "../services/Fan/FanCommand.h"

Test::Test(Messaging *messaging, Dimmer *dimmer) {
    this->messaging = messaging;
    this->dimmer = dimmer;
}

void Test::handle(Message* event) {
    if (runningState == Application::RunningState::FOREGROUND) {
        auto userInput = static_cast<UserInput*>(event);
        switch (userInput->event) {
            case UserInput::UserInputEvent::DIAL_PLUS:
                plus();
                break;
            case UserInput::UserInputEvent::DIAL_MINUS:
                minus();
                break;
            case UserInput::UserInputEvent::BUTTON_ENTER_RELEASED:
                messaging->send(new FanCommand(dial));
                break;
            case UserInput::UserInputEvent::DIAL_BUTTON_RELEASED:
                messaging->send(new FanCommand(0));
                break;
            default:
                break;
        }
    }
}

void Test::plus() {
    dial++;
    dimmer->setPosition(dial);
    renderUI();
}

void Test::minus() {
    dial--;
    dimmer->setPosition(dial);
    renderUI();
}

void Test::renderUI() {
    auto *s = new char[4];
    sprintf(s, "%03u", dial);
    messaging->send(new DrawText(11, 0, s));
}

void Test::toForeground() {
    Application::toForeground();
    renderUI();
}

void Test::toBackground() {
    Application::toBackground();
}

char *Test::title() {
    return new char[] {
        'M', 'a',
        'n', 'u',
        'a', 'l',
        0x00
    };
}
