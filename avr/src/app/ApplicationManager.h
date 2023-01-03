//
// Created by ghisi on 1/2/23.
//

#ifndef AVR_APPLICATIONMANAGER_H
#define AVR_APPLICATIONMANAGER_H


#include "Application.h"
#include "../system/Subscriber.h"
#include "list"
#include "../system/Messaging.h"
#include "../system/AsyncChain.h"

class ApplicationManager: public Subscriber {
public:
    explicit ApplicationManager(Messaging *messaging, std::list<Application*> apps);
    void handle(Message *event) override;

    void start();

protected:
    AsyncChain *titleDisplay = nullptr;
private:
    void previousApp();
    void nextApp();
    std::list<Application*> apps;
    Application *foreground = nullptr;
    Messaging *messaging;
    void clearUI();

    void runForeground();
};


#endif //AVR_APPLICATIONMANAGER_H
