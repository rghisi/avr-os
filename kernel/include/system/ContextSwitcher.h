//
// Created by ghisi on 16.11.23.
//

#ifndef AVR_CONTEXTSWITCHER_H
#define AVR_CONTEXTSWITCHER_H

#include "Task.h"

class ContextSwitcher {
public:
    virtual void startTask(Task *task) = 0;
    virtual void switchToTask(Task *task) = 0;
    virtual void yield(Task* task) = 0;
};
#endif //AVR_CONTEXTSWITCHER_H
