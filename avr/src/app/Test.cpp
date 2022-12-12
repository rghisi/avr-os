//
// Created by ghisi on 12.12.22.
//

#include "Test.h"
#include "../input/UserInput.h"
#include "cstdio"

EventType Test::eventType() {
    return USER_INPUT;
}

Test::Test(EventDispatcher *eventDispatcher, Dimmer *dimmer) {
    this->eventDispatcher = eventDispatcher;
    this->dimmer = dimmer;
}

bool Test::handle(std::unique_ptr<Event> event) {
    auto userInput = static_cast<UserInput*>(event->data());
    switch (userInput->event) {
        case UserInput::Event::DIAL_PLUS:
            plus();
            break;
        case UserInput::Event::DIAL_MINUS:
            minus();
            break;
        default:
            break;
    }
    delete userInput;
    return true;
}

void Test::plus() {
    dial++;
    dimmer->setPosition(dial);
    auto s = new char[4];
    sprintf(s, "%" PRIu8, dial);
    auto event = std::make_unique<Event>(Event(EventType::SHOW_TEXT_REQUESTED, s));
    eventDispatcher->dispatch(std::move(event));
}

void Test::minus() {
    dial--;
    dimmer->setPosition(dial);
    auto s = new char[4];
    sprintf(s, "%" PRIu8, dial);
    auto event = std::make_unique<Event>(Event(EventType::SHOW_TEXT_REQUESTED, s));
    eventDispatcher->dispatch(std::move(event));
}