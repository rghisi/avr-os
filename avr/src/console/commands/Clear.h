//
// Created by ghisi on 19.11.23.
//

#ifndef AVR_CLEAR_H
#define AVR_CLEAR_H

#include "cstdint"
#include "../ShellCommand.h"
#include "../../comms/Serial.h"

class Clear: public ShellCommand {
public:
    explicit Clear() : ShellCommand("clear") {
    }

    void run(char* args) override {
        Serial::send(CLEAR_SCREEN, CLEAR_SCREEN_SIZE);
    }

private:
    static constexpr const char* CLEAR_SCREEN = "\x1b[2J\x1b[H";
    static constexpr const uint_fast8_t CLEAR_SCREEN_SIZE = 7;
};
#endif //AVR_CLEAR_H
