//
// Created by ghisi on 16.11.23.
//

#ifndef AVR_CONSOLELINEHANDLER_H
#define AVR_CONSOLELINEHANDLER_H

#include "cstdint"
#include "cstddef"

class ConsoleLineHandler {
public:
    virtual void handle(char *line) = 0;
};

#endif //AVR_CONSOLELINEHANDLER_H
