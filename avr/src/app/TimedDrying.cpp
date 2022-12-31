//
// Created by ghisi on 12/30/22.
//

#include "TimedDrying.h"
#include "../time/TimeTickData.h"
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

bool TimedDrying::handle(std::unique_ptr<Event> event) {
    switch (event->type()) {
        case TIME_TICK:
            handleTimeTick(std::move(event));
            break;
        case USER_INPUT:
            handleUserInput(std::move(event));
            break;
        default:
            break;
    }

    return true;
}

void TimedDrying::handleTimeTick(std::unique_ptr<Event> event) {
    auto timeTickData = static_cast<TimeTickData*>(event->data());
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
    delete timeTickData;
}

void TimedDrying::handleUserInput(std::unique_ptr<Event> event) {
    auto userInput = static_cast<UserInput*>(event->data());
    if (active) {
        switch (userInput->event) {
            case UserInput::Event::DIAL_PLUS:
                //increase selected
                break;
            case UserInput::Event::DIAL_MINUS:
                //decrease selected
                break;
            case UserInput::Event::BUTTON_RIGHT_RELEASED:
                //cycle next - minutes, seconds, none
                break;
            case UserInput::Event::BUTTON_LEFT_RELEASED:
                //cycle previous - minutes, seconds, none
                break;
            case UserInput::Event::BUTTON_ENTER_RELEASED:
                //start/pause timer
                break;
            case UserInput::Event::DIAL_BUTTON_RELEASED:
                //reset timer
                break;
            default:
                break;
        }
    }
    delete userInput;
}

void TimedDrying::activate() {
    active = true;
}

void TimedDrying::deactivate() {
    active = false;
}
