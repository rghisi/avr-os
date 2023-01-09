//
// Created by ghisi on 1/2/23.
//

#include "ApplicationManager.h"
#include "../input/UserInput.h"
#include "../lcd/ClearDisplay.h"
#include "cstdio"
#include "../lcd/DrawText.h"

ApplicationManager::ApplicationManager(Messaging *messaging, std::list<Application*> apps) {
    this->messaging = messaging;
    this->apps = std::move(apps);
}

void ApplicationManager::handle(Message *event) {
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
}

void ApplicationManager::previousApp() {
    if (foreground == nullptr || !foreground->isRunning()) {
        if (foreground != nullptr) {
            foreground->toBackground();
            apps.push_front(foreground);
        }
        foreground = apps.back();
        apps.pop_back();
        runForeground();
    }
}

void ApplicationManager::nextApp() {
    if (foreground == nullptr || !foreground->isRunning()) {
        if (foreground != nullptr) {
            foreground->toBackground();
            apps.push_back(foreground);
        }
        foreground = apps.front();
        apps.pop_front();
        runForeground();
    }
}

void ApplicationManager::runForeground() {
    if (titleDisplay != nullptr && !titleDisplay->isCancelled()) {
        titleDisplay->cancel();
    }
    titleDisplay = new AsyncChain(messaging);
    titleDisplay
            ->then([this](){
                messaging->send(new DrawText(0, 0, foreground->title()));
            })
            ->wait(800)
            ->then([this](){
                messaging->send(new ClearDisplay());
            })
            ->then([this](){
                foreground->toForeground();
            })
            ->schedule();
}

void ApplicationManager::clearUI() {
    messaging->send(new ClearDisplay());
}

void ApplicationManager::start() {
    clearUI();
    nextApp();
}
