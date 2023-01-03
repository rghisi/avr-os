//
// Created by ghisi on 1/2/23.
//

#include "cstdio"
#include "TimedMultiTrayDrying.h"
#include "../system/Math.h"
#include "../lcd/DrawText.h"
#include "../lcd/EnableCursor.h"
#include "../lcd/DisableCursor.h"

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
            default:
                break;
        }
    }
}

void TimedMultiTrayDrying::updateTimers() {
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
        }
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
            setTemperature = Math::max(0, Math::min(70, setTemperature));
            break;
        case MINUTES:
            setMinutes += amount;
            setMinutes = Math::max(0, Math::min(120, setMinutes));
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
    auto firstLine = new char[17];
    firstLine[16] = 0;
    sprintf(firstLine, "%02" PRIi8 "m %02" PRIi8 "C Desl.", setMinutes, setTemperature);
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
            "A%02" PRIi8 " B%02" PRIi8 " C%02" PRIi8 " D%02" PRIi8,
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
}

void TimedMultiTrayDrying::renderTickTock() {
    tickTock = !tickTock;
    auto string = new char[2];
    string[0] = tickTock ? '.' : ' ';
    string[1] = 0x00;
    messaging->send(new DrawText(TICK_TOCK_X, SECOND_LINE, string));
}
