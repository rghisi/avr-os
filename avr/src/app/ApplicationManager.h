//
// Created by ghisi on 1/2/23.
//

#ifndef AVR_APPLICATIONMANAGER_H
#define AVR_APPLICATIONMANAGER_H


#include "Application.h"
#include "../system/EventHandler.h"
#include "list"
#include "../system/Messaging.h"

class ApplicationManager: public EventHandler {
public:
    explicit ApplicationManager(Messaging *messaging, std::list<Application*> apps);
    bool handle(Message *event) override;
private:
    static constexpr MessageType messageTypes[] = {USER_INPUT};
    static constexpr uint8_t messageTypeCount = 1;
    void previousApp();
    void nextApp();
    std::list<Application*> apps;
    Application *foreground = nullptr;
    Messaging *messaging;

    void clearUI();
};


#endif //AVR_APPLICATIONMANAGER_H
