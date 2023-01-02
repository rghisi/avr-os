//
// Created by ghisi on 1/2/23.
//

#ifndef AVR_APPLICATIONMANAGER_H
#define AVR_APPLICATIONMANAGER_H


#include "Application.h"
#include "../system/EventHandler.h"

class ApplicationManager: public EventHandler {
public:
    ApplicationManager(Application* apps);
};


#endif //AVR_APPLICATIONMANAGER_H
