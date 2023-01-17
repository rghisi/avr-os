//
// Created by ghisi on 12/30/22.
//

#include "cstdio"
#include "algorithm"
#include "../system/Math.h"
#include "TimedDrying.h"
#include "../lcd/DrawText.h"
#include "../lcd/EnableCursor.h"
#include "../lcd/DisableCursor.h"
#include "../tasks/TemperatureControlCommand.h"
#include "../services/buzzer/BuzzerCommand.h"
#include "../services/Fan/FanCommand.h"

TimedDrying::TimedDrying(Messaging *messageDispatcher, Timer *timer) {
    this->messaging = messageDispatcher;
    this->timer = timer;
    seconds = setSeconds;
    minutes = setMinutes;
}

void TimedDrying::handle(Message *event) {
    if (runningState != Application::RunningState::BACKGROUND) {
        switch (event->type()) {
            case TIMER_STATE:;
                handleTimerState(static_cast<TimerState *>(event));
                break;
            case USER_INPUT:
                handleUserInput(static_cast<UserInput *>(event));
                break;
            case CLIMATE_REPORT:
                handleClimateReport(static_cast<ClimateReport *>(event));
                break;
            case TEMPERATURE_CONTROL_STATUS:
                handleTemperatureControlStatus(static_cast<TemperatureControlStatus *>(event));
                break;
            default:
                break;
        }
    }
}

void TimedDrying::handleTimerState(TimerState *timerState) {
    switch (timerState->state) {
        case Timer::State::STOPPED:
            stop();
            break;
        case Timer::State::RUNNING:
            this->seconds = timerState->seconds;
            this->minutes = timerState->minutes;
            renderCountdown();
            break;
        case Timer::State::PAUSED:
            break;
        case Timer::State::FINISHED:
            finish();
            break;
        default:
            break;
    }
}

void TimedDrying::handleUserInput(UserInput *userInput) {
    switch (userInput->event) {
        case UserInput::UserInputEvent::DIAL_PLUS:
            changeSelected(1);
            renderSetTimer();
            renderSetClimate();
            break;
        case UserInput::UserInputEvent::DIAL_MINUS:
            changeSelected(-1);
            renderSetTimer();
            renderSetClimate();
            break;
        case UserInput::UserInputEvent::BUTTON_RIGHT_RELEASED:
            cycleSelection(1);
            renderCursor();
            break;
        case UserInput::UserInputEvent::BUTTON_LEFT_RELEASED:
            cycleSelection(-1);
            renderCursor();
            break;
        case UserInput::UserInputEvent::BUTTON_ENTER_RELEASED:
            startStop();
            renderCountdown();
            renderCursor();
            break;
        case UserInput::UserInputEvent::DIAL_BUTTON_RELEASED:
            break;
        default:
            break;
    }
}

void TimedDrying::handleClimateReport(ClimateReport *climateReport) {
    auto string = new char[8];
    string[7] = 0x00;
    uint8_t temperature = Math::divBy10(Math::divBy10(climateReport->temperatureCelsius));
    uint8_t humidity = climateReport->relativeHumidity >> 10;
    sprintf(string, "%02uC %02u%%", temperature, humidity);
    messaging->send(new DrawText(CLIMATE_X_POSITION, CURRENT_VALUES_Y_POSITION, string));
}

void TimedDrying::handleTemperatureControlStatus(TemperatureControlStatus *temperatureControlStatus) {
    auto string = new char[7];
    string[6] = 0x00;
    if (temperatureControlStatus->enabled) {
        sprintf(string, "P%05u", temperatureControlStatus->position);
    } else {
        sprintf(string, "Desl. ");
    }
    messaging->send(new DrawText(4, SET_POINT_Y_POSITION, string));
}

void TimedDrying::cycleSelection(int8_t amount) {
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
    renderCursor();
}

void TimedDrying::renderCountdown() {
    auto countdownAsString = new char[7];
    countdownAsString[6] = 0;
    switch (countdownState) {
        case State::STOPPED:
            sprintf(countdownAsString, "Parado");
            break;
        case State::RUNNING:
            sprintf(countdownAsString, " %02i:%02i", minutes, seconds);
            break;
        case State::FINISHED:
            sprintf(countdownAsString, "Pronto");
    }
    messaging->send(new DrawText(RUNNING_TIMER_X_POSITION, CURRENT_VALUES_Y_POSITION, countdownAsString));
}

void TimedDrying::renderSetTimer() {
    auto setTimerAsString = new char[6];
    setTimerAsString[5] = 0x00;
    sprintf(setTimerAsString, "%02i:%02i ", setMinutes, setSeconds);
    messaging->send(new DrawText(TIMER_X_POSITION, SET_POINT_Y_POSITION, setTimerAsString));
}

void TimedDrying::renderCursor() {
    if (selection > NONE && selection < MAX && countdownState != State::RUNNING) {
        messaging->send(new EnableCursor(cursorX, SET_POINT_Y_POSITION));
    } else {
        messaging->send(new DisableCursor());
    }
}

void TimedDrying::renderSetClimate() {
    auto string = new char[4];
    string[3] = 0x00;
    sprintf(string, "%02iC", setTemperature);
    messaging->send(new DrawText(CLIMATE_X_POSITION, SET_POINT_Y_POSITION, string));
}

void TimedDrying::renderClimate() {

}

void TimedDrying::toForeground() {
    Application::toForeground();
    renderUI();
}

void TimedDrying::toBackground() {
    Application::toBackground();
}

void TimedDrying::changeSelected(int8_t amount) {
    switch (selection) {
        case TEMPERATURE:
            setTemperature += amount;
            setTemperature = Math::max((int8_t)0, Math::min((int8_t)70, setTemperature));
            break;
        case MINUTES:
            setMinutes += amount;
            setMinutes = Math::max((int8_t)0, Math::min((int8_t)120, setMinutes));
            break;
        case SECONDS:
            setSeconds += amount;
            setSeconds = Math::max((int8_t)0, Math::min((int8_t)59, setSeconds));
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
    runningState = Application::RunningState::FOREGROUND;
    countdownState = State::STOPPED;
    timer->stop();
    messaging->send(new TemperatureControlCommand(false, setTemperature, 0));
    messaging->send(new FanCommand(FanCommand::OFF));
    renderCountdown();
    renderStatus();
}

void TimedDrying::start() {
    runningState = Application::RunningState::RUNNING;
    countdownState = State::RUNNING;
    minutes = setMinutes;
    seconds = setSeconds;
    timer->start(setMinutes, setSeconds);
    messaging->send(new TemperatureControlCommand(true, setTemperature, 0));
    messaging->send(new FanCommand(fanPower));
    renderCountdown();
    renderStatus();
}

void TimedDrying::finish() {
    runningState = Application::RunningState::FOREGROUND;
    countdownState = State::FINISHED;
    messaging->send(new TemperatureControlCommand(false, setTemperature, 0));
    messaging->send(new FanCommand(FanCommand::OFF));
    renderCountdown();
    renderStatus();
    messaging->send(new BuzzerCommand(150));
}

char *TimedDrying::title() {
    return new char[] {
        'T', 'e', 'm', 'p',
        'o', 'r', 'i','z',
        'a','d','o','r',
        0x00
    };
}

void TimedDrying::renderStatus() {

}
