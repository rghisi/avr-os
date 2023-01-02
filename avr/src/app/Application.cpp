//
// Created by ghisi on 1/2/23.
//

#include "Application.h"

void Application::stop() {
    runningState = RunningState::STOPPED;
}

void Application::toForeground() {
    runningState = RunningState::RUNNING_FOREGROUND;
}

void Application::toBackground() {
    runningState = RunningState::RUNNING_BACKGROUND;
}

