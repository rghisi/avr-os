//
// Created by ghisi on 18.11.23.
//

#ifndef AVR_APP_H
#define AVR_APP_H

#include "../system/Task.h"

class App {
public:
    const char* name;
    virtual Task* load() = 0;
};
#endif //AVR_APP_H
