//
// Created by ghisi on 1/2/23.
//

#include "cstdio"
#include "TimedMultiTrayDrying.h"
#include "../system/Math.h"
#include "../lcd/DrawText.h"
#include "../lcd/EnableCursor.h"
#include "../lcd/DisableCursor.h"
#include "../tasks/TemperatureControlCommand.h"
#include "../tasks/TemperatureControlStatus.h"
#include "../services/Fan/FanCommand.h"

TimedMultiTrayDrying::TimedMultiTrayDrying(Messaging *messaging) {
    this->messaging = messaging;
    std::fill_n(seconds.begin(), seconds.size(), 0);
    std::fill_n(minutes.begin(), minutes.size(), 0);
}

void TimedMultiTrayDrying::handle(Message *event) {
    if (runningState == Application::RunningState::FOREGROUND) {
        switch (event->type()) {
            case TIME_TICK:
                updateTimers();
                renderTimers();
                renderTickTock();
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

void TimedMultiTrayDrying::updateTimers() {
    uint8_t zeroedTimers = 0;
    for (uint8_t i = 0; i < seconds.size(); i++) {
        int8_t s = seconds[i];
        int8_t m = minutes[i];
        if (s > 0 || m > 0) {
            s--;
            if (s < 0) {
                s = 59;
                m--;
                if (m < 0) {
                    m = 0;
                }
            }
            seconds[i] = s;
            minutes[i] = m;
            if (s == 0 && m == 0) {
                zeroedTimers++;
            }
        }
    }
    if (zeroedTimers == NUMBER_OF_TRAYS) {
        stopDrying();
    }
}

void TimedMultiTrayDrying::handleUserInput(UserInput *userInput) {
    switch (userInput->event) {
        case UserInput::UserInputEvent::DIAL_PLUS:
            changeSelected(1);
            renderSetPoints();
            renderCursor();
            break;
        case UserInput::UserInputEvent::DIAL_MINUS:
            changeSelected(-1);
            renderSetPoints();
            renderCursor();
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
            startSelectedTrayTimer();
            renderTimers();
            renderCursor();
            break;
        case UserInput::UserInputEvent::DIAL_BUTTON_RELEASED:
            break;
        default:
            break;
    }
}

void TimedMultiTrayDrying::handleClimateReport(ClimateReport *climateReport) {
    auto firstLine = new char[4];
    firstLine[3] = 0;
    uint8_t temperature = Math::divBy10(Math::divBy10(climateReport->temperatureCelsius));
    sprintf(firstLine, "%02uC", temperature);
    messaging->send(new DrawText(TEMPERATURE_X, FIRST_LINE, firstLine));
}

void TimedMultiTrayDrying::handleTemperatureControlStatus(TemperatureControlStatus *temperatureControlStatus) {
    auto firstLine = new char[5];
    firstLine[4] = 0;
    if (temperatureControlStatus->enabled) {
        uint16_t position = Math::divBy10(temperatureControlStatus->position);
        sprintf(firstLine, "%04u", position);
    } else {
        sprintf(firstLine, "Desl");
    }
    messaging->send(new DrawText(POWER_X, FIRST_LINE, firstLine));
}

void TimedMultiTrayDrying::toForeground() {
    Application::toForeground();
    renderUI();
}

void TimedMultiTrayDrying::toBackground() {
    Application::toBackground();
}

char *TimedMultiTrayDrying::title() {
    return new char[] {'B', 'a', 'n', 'd', 'e', 'j', 'a', 0x00};
}

void TimedMultiTrayDrying::cycleSelection(int8_t amount) {
    auto s = (int8_t) selection;
    s += amount;
    if (s == Selection::MAX) {
        s = 0;
    } else if (s < 0) {
        s = Selection::MAX - 1;
    }
    selection = (Selection) s;
}

void TimedMultiTrayDrying::changeSelected(int8_t amount) {
    switch (selection) {
        case TEMPERATURE:
            setTemperature += amount;
            setTemperature = Math::max((int8_t)0, Math::min((int8_t)70, setTemperature));
            break;
        case MINUTES:
            setMinutes += amount;
            setMinutes = Math::max((int8_t)0, Math::min((int8_t)120, setMinutes));
            break;
        default:
            break;
    }
}

void TimedMultiTrayDrying::renderUI() {
    renderSetPoints();
    renderTimers();
    renderCursor();
}

void TimedMultiTrayDrying::renderCursor() {
    switch (selection) {
        case TEMPERATURE:
            messaging->send(new EnableCursor(TEMPERATURE_CURSOR_X, FIRST_LINE));
            break;
        case MINUTES:
            messaging->send(new EnableCursor(MINUTES_CURSOR_X, FIRST_LINE));
            break;
        case TRAY_A:
            messaging->send(new EnableCursor(TRAY_A_CURSOR_X, SECOND_LINE));
            break;
        case TRAY_B:
            messaging->send(new EnableCursor(TRAY_B_CURSOR_X, SECOND_LINE));
            break;
        case TRAY_C:
            messaging->send(new EnableCursor(TRAY_C_CURSOR_X, SECOND_LINE));
            break;
        case TRAY_D:
            messaging->send(new EnableCursor(TRAY_D_CURSOR_X, SECOND_LINE));
            break;
        default:
            messaging->send(new DisableCursor());
            break;
    }
}

void TimedMultiTrayDrying::renderSetPoints() {
    auto firstLine = new char[8];
    firstLine[7] = 0;
    sprintf(firstLine, "%02im %02iC", setMinutes, setTemperature);
    messaging->send(new DrawText(SET_POINTS_X, FIRST_LINE, firstLine));
}

void TimedMultiTrayDrying::renderTimers() {
    auto lineTwo = new char[17];
    lineTwo[16] = 0;
    int8_t timers[4] = {
            minutes[0] > 0 ? minutes[0] : seconds[0],
            minutes[1] > 0 ? minutes[1] : seconds[1],
            minutes[2] > 0 ? minutes[2] : seconds[2],
            minutes[3] > 0 ? minutes[3] : seconds[3],
    };
    sprintf(
            lineTwo,
            "A%02i B%02i C%02i D%02i",
            timers[0], timers[1], timers[2], timers[3]
            );
    messaging->send(new DrawText(TIMERS_X, SECOND_LINE, lineTwo));
    renderCursor();
}

void TimedMultiTrayDrying::startSelectedTrayTimer() {
    switch (selection) {
        case TRAY_A:
            seconds[0] = 0;
            minutes[0] = setMinutes;
            break;
        case TRAY_B:
            seconds[1] = 0;
            minutes[1] = setMinutes;
            break;
        case TRAY_C:
            seconds[2] = 0;
            minutes[2] = setMinutes;
            break;
        case TRAY_D:
            seconds[3] = 0;
            minutes[3] = setMinutes;
            break;
        default:
            break;
    }
    messaging->send(new TemperatureControlCommand(true, setTemperature, 0));
    messaging->send(new FanCommand(160));
}

void TimedMultiTrayDrying::renderTickTock() {
    tickTock = !tickTock;
    auto string = new char[2];
    string[0] = tickTock ? '.' : ' ';
    string[1] = 0x00;
    messaging->send(new DrawText(TICK_TOCK_X, SECOND_LINE, string));
}

void TimedMultiTrayDrying::stopDrying() {
    messaging->send(new TemperatureControlCommand(false, setTemperature, 0));
    messaging->send(new FanCommand(160));
}
