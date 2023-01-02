//
// Created by ghisi on 12/30/22.
//

#include "cstdio"
#include "algorithm"
#include "TimedDrying.h"
#include "../input/UserInput.h"
#include "../lcd/DrawText.h"
#include "../lcd/EnableCursorCommand.h"
#include "../lcd/DisableCursor.h"
#include "../tasks/ClimateControl.h"

TimedDrying::TimedDrying(Messaging *messageDispatcher) {
    this->messaging = messageDispatcher;
    setMinutes = 15;
    setSeconds = 0;
    setTemperature = 40;
    temperature = 0;
    humidity = 0;
    seconds = setSeconds;
    minutes = setMinutes;
    previousTimestamp = 0;
}

bool TimedDrying::handle(Message *event) {
    switch (event->type()) {
        case TIME_TICK:
            TimeTick* timeTick;
            timeTick = static_cast<TimeTick*>(event);
            updateCountdown(timeTick);
            updateTimestamp(timeTick);
            break;
        case USER_INPUT:
            handleUserInput(event);
            break;
        case CLIMATE_REPORT:
            ClimateReport* climateReport;
            climateReport = static_cast<ClimateReport*>(event);
            handleClimateReport(climateReport);
            renderClimate();
            break;
        default:
            break;
    }

    return true;
}

void TimedDrying::updateCountdown(TimeTick *timeTick) {
    if (countdownState == State::RUNNING) {
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
        if (minutes < 0) {
            finish();
        }
        renderCountdown();
    }
}

void TimedDrying::handleUserInput(Message *event) {
    if (runningState == Application::RunningState::FOREGROUND) {
        auto userInput = static_cast<UserInput *>(event);
        switch (userInput->event) {
            case UserInput::UserInputEvent::DIAL_PLUS:
                changeSelection(1);
                renderSetTimer();
                renderSetClimate();
                break;
            case UserInput::UserInputEvent::DIAL_MINUS:
                changeSelection(-1);
                renderSetTimer();
                renderSetClimate();
                break;
            case UserInput::UserInputEvent::BUTTON_RIGHT_RELEASED:
                changeUISelection(1);
                renderCursor();
                break;
            case UserInput::UserInputEvent::BUTTON_LEFT_RELEASED:
                changeUISelection(-1);
                renderCursor();
                break;
            case UserInput::UserInputEvent::BUTTON_ENTER_RELEASED:
                startStop();
                renderCountdown();
                renderCursor();
                break;
            case UserInput::UserInputEvent::DIAL_BUTTON_RELEASED:
                resetCountdown();
                renderCountdown();
                break;
            default:
                break;
        }
    }
}

void TimedDrying::handleClimateReport(ClimateReport *climateReport) {
    this->temperature = climateReport->temperatureCelsius;
    this->humidity = climateReport->relativeHumidity;
}

void TimedDrying::changeUISelection(int8_t amount) {
    auto s = (int8_t) selection;
    s += amount;
    if (s == Selection::MAX) {
        s = 0;
    } else if (s < 0) {
        s = Selection::MAX - 1;
    }
    selection = (Selection) s;
    switch (selection) {
        case NONE:
            cursorX = 0;
            break;
        case TEMPERATURE:
            cursorX = CLIMATE_X_POSITION + 1;
            break;
        case MINUTES:
            cursorX = TIMER_X_POSITION + 1;
            break;
        case SECONDS:
            cursorX = TIMER_X_POSITION + 4;
            break;
        default:
            break;
    }
}

void TimedDrying::renderUI() {
    renderSetClimate();
    renderSetTimer();
    renderCountdown();
    renderClimate();
    renderCursor();
}

void TimedDrying::renderCountdown() {
    if (runningState == Application::RunningState::FOREGROUND) {
        auto countdownAsString = new char[7];
        countdownAsString[6] = 0;
        switch (countdownState) {
            case State::STOPPED:
                sprintf(countdownAsString, "Parado");
                break;
            case State::RUNNING:
                sprintf(countdownAsString, "%02" PRIi8 ":%02" PRIi8 " ", minutes, seconds);
                break;
            case State::FINISHED:
                sprintf(countdownAsString, "Pronto");
        }
        messaging->send(new DrawText(TIMER_X_POSITION, CURRENT_VALUES_Y_POSITION, countdownAsString));
    }
}

void TimedDrying::renderSetTimer() {
    if (runningState == Application::RunningState::FOREGROUND) {
        auto setTimerAsString = new char[7];
        setTimerAsString[6] = 0x00;
        sprintf(setTimerAsString, "%02" PRIi8 ":%02" PRIi8 " ", setMinutes, setSeconds);
        messaging->send(new DrawText(TIMER_X_POSITION, SET_POINT_Y_POSITION, setTimerAsString));
    }
}

void TimedDrying::renderCursor() {
    if (runningState == Application::RunningState::FOREGROUND) {
        if (selection > NONE && selection < MAX && countdownState != State::RUNNING) {
            messaging->send(new EnableCursorCommand(cursorX, SET_POINT_Y_POSITION));
        } else {
            messaging->send(new DisableCursor());
        }
    }
}

void TimedDrying::renderSetClimate() {
    if (runningState == Application::RunningState::FOREGROUND) {
        auto string = new char[7];
        string[6] = 0x00;
        sprintf(string, "%02" PRIu8 "C", setTemperature);
        messaging->send(new DrawText(CLIMATE_X_POSITION, SET_POINT_Y_POSITION, string));
    }
}

void TimedDrying::renderClimate() {
    if (runningState == Application::RunningState::FOREGROUND) {
        auto string = new char[8];
        string[7] = 0x00;
        sprintf(string, "%02" PRIu8 "C %02" PRIu8 "%%", temperature, humidity);
        messaging->send(new DrawText(CLIMATE_X_POSITION, CURRENT_VALUES_Y_POSITION, string));
    }
}

void TimedDrying::toForeground() {
    Application::toForeground();
    renderUI();
}

void TimedDrying::toBackground() {
    Application::toBackground();
}

void TimedDrying::updateTimestamp(TimeTick *timeTick) {
    previousTimestamp = timeTick->millis();
}

void TimedDrying::changeSelection(int8_t amount) {
    switch (selection) {
        case TEMPERATURE:
            setTemperature += amount;
            setTemperature = max(0, min(70, setTemperature));
            break;
        case MINUTES:
            setMinutes += amount;
            setMinutes = max(0, min(120, setMinutes));
            break;
        case SECONDS:
            setSeconds += amount;
            setSeconds = max(0, min(59, setSeconds));
            break;
        default:
            break;
    }
}

void TimedDrying::startStop() {
    switch (countdownState) {
        case State::STOPPED:
            start();
            break;
        case State::RUNNING:
            stop();
            break;
        case State::FINISHED:
            start();
            break;
    }
}

void TimedDrying::stop() {
    messaging->send(new ClimateControl(false, setTemperature, 0));
    countdownState = State::STOPPED;
}

void TimedDrying::start() {
    messaging->send(new ClimateControl(true, setTemperature, 0));
    resetCountdown();
    countdownState = State::RUNNING;
}

void TimedDrying::resetCountdown() {
    milliseconds = 0;
    seconds = setSeconds;
    minutes = setMinutes;
}

void TimedDrying::finish() {
    messaging->send(new ClimateControl(false, setTemperature, 0));
    countdownState = State::FINISHED;
}

int8_t TimedDrying::max(int8_t a, int8_t b) {
    return a > b ? a : b;
}

int8_t TimedDrying::min(int8_t a, int8_t b) {
    return a < b ? a : b;
}
