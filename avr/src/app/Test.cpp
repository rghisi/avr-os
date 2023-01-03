//
// Created by ghisi on 12.12.22.
//

#include "Test.h"
#include "../input/UserInput.h"
#include "cstdio"
#include "../lcd/DrawText.h"

Test::Test(Messaging *eventDispatcher, Dimmer *dimmer) {
    this->eventDispatcher = eventDispatcher;
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
    auto s = new char[4];
    s[3] = 0;
    sprintf(s, "%03" PRIu8, dial);
    eventDispatcher->send(new DrawText(11, 0, s));
}

void Test::toForeground() {
    Application::toForeground();
    renderUI();
}

void Test::toBackground() {
    Application::toBackground();
}

char *Test::title() {
    return new char[] {'T', 'e', 's', 't', 0x00};
}
