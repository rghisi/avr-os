//
// Created by ghisi on 12/30/22.
//

#include "TimedDrying.h"
#include "../time/TimeTick.h"
#include "../input/UserInput.h"
#include "cstdio"
#include "../lcd/DrawText.h"
#include "../lcd/DisplayCommand.h"
#include "../lcd/EnableCursorCommand.h"

TimedDrying::TimedDrying(MessageDispatcher *messageDispatcher) {
    this->messageDispatcher = messageDispatcher;
    minutes = 0;
    seconds = 0;
    active = false;
    previousTimestamp = 0;
}

MessageType TimedDrying::eventType() {
    return TIME_TICK;
}

bool TimedDrying::handle(Message* event) {
    if (active) {
        switch (event->type()) {
            case TIME_TICK:
                handleTimeTick(event);
                break;
            case USER_INPUT:
                handleUserInput(event);
                break;
            default:
                break;
        }
    }

    return true;
}

void TimedDrying::handleTimeTick(Message* message) {
    auto timeTick = static_cast<TimeTick*>(message);
    auto timestamp = timeTick->millis();
    auto delta = timestamp - previousTimestamp;
    auto sec = delta / 1000;
    seconds += sec;
    if (seconds > 59) {
        minutes++;
        seconds -= 60;
    }
    auto s = new char[6];
    sprintf(s, "%02" PRIu8 ":%02" PRIu8, minutes, seconds);
    messageDispatcher->dispatch(DisplayCommand::drawText(10, 1, s));
    previousTimestamp = timestamp;
}

void TimedDrying::handleUserInput(Message* event) {
    auto userInput = static_cast<UserInput*>(event);
    switch (userInput->event) {
        case UserInput::UserInputEvent::DIAL_PLUS:
            //increase selected
            break;
        case UserInput::UserInputEvent::DIAL_MINUS:
            //decrease selected
            break;
        case UserInput::UserInputEvent::BUTTON_RIGHT_RELEASED:
            //cycle next - minutes, seconds, none
            break;
        case UserInput::UserInputEvent::BUTTON_LEFT_RELEASED:
            //cycle previous - minutes, seconds, none
            break;
        case UserInput::UserInputEvent::BUTTON_ENTER_RELEASED:
            //start/pause timer
            seconds = 0;
            minutes = 0;
            render();
            break;
        case UserInput::UserInputEvent::DIAL_BUTTON_RELEASED:
            //reset timer
            break;
        default:
            break;
    }
}

void TimedDrying::render() { messageDispatcher->dispatch(DisplayCommand::enableCursor(10, 1)); }

void TimedDrying::activate() {
    active = true;
}

void TimedDrying::deactivate() {
    active = false;
}
