//
// Created by ghisi on 1/2/23.
//

#include "Application.h"

void Application::toForeground() {
    runningState = RunningState::FOREGROUND;
}

void Application::toBackground() {
    runningState = RunningState::BACKGROUND;
}

