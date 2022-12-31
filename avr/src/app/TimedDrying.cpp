//
// Created by ghisi on 12/30/22.
//

#include "TimedDrying.h"
#include "../time/TimeTick.h"
#include "../input/UserInput.h"

TimedDrying::TimedDrying() {
    minutes = 0;
    seconds = 0;
    active = false;
    previousTimestamp = 0;
}

EventType TimedDrying::eventType() {
    return TIME_TICK;
}

bool TimedDrying::handle(Event* event) {
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

    return true;
}

void TimedDrying::handleTimeTick(Event* event) {
    auto timeTickData = static_cast<TimeTick*>(event);
    auto timestamp = timeTickData->millis();
    if (active) {
        auto delta = timestamp - previousTimestamp;
        auto sec = delta / 1000;
        seconds += sec;
        if (seconds > 59) {
            minutes++;
            seconds -= 59;
        }
    }
    previousTimestamp = timestamp;
}

void TimedDrying::handleUserInput(Event* event) {
    auto userInput = static_cast<UserInput*>(event);
    if (active) {
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
                break;
            case UserInput::UserInputEvent::DIAL_BUTTON_RELEASED:
                //reset timer
                break;
            default:
                break;
        }
    }
}

void TimedDrying::activate() {
    active = true;
}

void TimedDrying::deactivate() {
    active = false;
}
