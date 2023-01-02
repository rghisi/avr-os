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

TimedDrying::TimedDrying(MessageDispatcher *messageDispatcher) : EventHandler(messageTypes, messageTypeCount) {
    this->messageDispatcher = messageDispatcher;
    setMinutes = 2;
    setSeconds = 0;
    seconds = setSeconds;
    minutes = setMinutes;
    previousTimestamp = 0;
}

bool TimedDrying::handle(Message *event) {
    switch (event->type()) {
        case TIME_TICK: {
            auto timeTick = static_cast<TimeTick*>(event);
            updateCountdown(timeTick);
            updateTimestamp(timeTick);
            break;
        }
        case USER_INPUT:
            handleUserInput(event);
            break;
        default:
            break;
    }

    return true;
}

void TimedDrying::updateCountdown(TimeTick *timeTick) {
    if (runningState != Application::RunningState::STOPPED) {
        auto timestamp = timeTick->millis();
        milliseconds += timestamp - previousTimestamp;
        if (milliseconds >= 1000) {
            milliseconds -= 1000;
            seconds--;
        }
        if (seconds < 0) {
            seconds += 60;
            minutes--;
        }
        renderCountdown();
    }
}

void TimedDrying::renderCountdown() {
    auto countdownAsString = new char[6];
    sprintf(countdownAsString, "%02" PRIi8 ":%02" PRIi8, minutes, seconds);
    messageDispatcher->dispatch(DisplayCommand::drawText(10, 1, countdownAsString));
}

void TimedDrying::renderSetTimer() {
    auto setTimerAsString = new char[6];
    sprintf(setTimerAsString, "%02" PRIi8 ":%02" PRIi8, setMinutes, setSeconds);
    messageDispatcher->dispatch(DisplayCommand::drawText(10, 0, setTimerAsString));
}

void TimedDrying::handleUserInput(Message *event) {
    auto userInput = static_cast<UserInput *>(event);
    switch (userInput->event) {
        case UserInput::UserInputEvent::DIAL_PLUS:
            //increase selected
            break;
        case UserInput::UserInputEvent::DIAL_MINUS:
            //decrease selected
            break;
        case UserInput::UserInputEvent::BUTTON_RIGHT_RELEASED:
            //cycle next - minutes, secondsCounter, none
            break;
        case UserInput::UserInputEvent::BUTTON_LEFT_RELEASED:
            //cycle previous - minutes, secondsCounter, none
            break;
        case UserInput::UserInputEvent::BUTTON_ENTER_RELEASED:
            //start/pause timer
            renderUI();
            break;
        case UserInput::UserInputEvent::DIAL_BUTTON_RELEASED:
            //reset timer
            break;
        default:
            break;
    }
}

void TimedDrying::renderUI() {
    renderSetTimer();
    renderCountdown();
    messageDispatcher->dispatch(DisplayCommand::enableCursor(10, 0));
}

void TimedDrying::stop() {
    Application::stop();
}

void TimedDrying::toForeground() {
    Application::toForeground();
}

void TimedDrying::toBackground() {
    Application::toBackground();
}

void TimedDrying::updateTimestamp(TimeTick *timeTick) {
    previousTimestamp = timeTick->millis();
}
