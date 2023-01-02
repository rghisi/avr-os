//
// Created by ghisi on 1/2/23.
//

#include "ApplicationManager.h"
#include "../input/UserInput.h"
#include "../lcd/ClearDisplay.h"

ApplicationManager::ApplicationManager(Messaging *messaging, std::list<Application*> apps) {
    this->messaging = messaging;
    this->apps = std::move(apps);
    nextApp();
}

bool ApplicationManager::handle(Message *event) {
    switch (event->type()) {
        case USER_INPUT:
            UserInput *userInput;
            userInput = static_cast<UserInput *>(event);
            switch (userInput->event) {
                case UserInput::UserInputEvent::BUTTON_UP_RELEASED:
                    clearUI();
                    previousApp();
                    break;
                case UserInput::UserInputEvent::BUTTON_DOWN_RELEASED:
                    clearUI();
                    nextApp();
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return false;
}

void ApplicationManager::previousApp() {
    if (foreground != nullptr) {
        foreground->toBackground();
        apps.push_front(foreground);
    }
    foreground = apps.back();
    apps.pop_back();
    foreground->toForeground();
}

void ApplicationManager::nextApp() {
    if (foreground != nullptr) {
        foreground->toBackground();
        apps.push_back(foreground);
    }
    foreground = apps.front();
    apps.pop_front();
    foreground->toForeground();
}

void ApplicationManager::clearUI() {
    messaging->send(new ClearDisplay());
}
