//
// Created by ghisi on 08.11.23.
//

#ifndef AVR_SHELL_H
#define AVR_SHELL_H

#include "ShellCommand.h"
#include "App.h"
#include "array"

class Shell: public Task {
public:
    Shell();
    [[noreturn]] void run() override;
    std::array<App*, 4> apps;
    std::array<ShellCommand*, 2> commands;
private:
    static constexpr uint_fast8_t COLUMNS = 40;
    static constexpr uint_fast8_t FIRST = 0;
    static constexpr uint_fast8_t LAST = COLUMNS - 1;
    static constexpr char BACKSPACE = '\b';
    static constexpr char CARRIAGE_RETURN = '\r';
    static constexpr char LINE_FEED = '\n';
    static constexpr const char* ERASE = "\x1b[J";
    static constexpr const uint_fast8_t ERASE_SIZE = 3;
    static constexpr const char* MOVE_ONE_RIGHT = "\x1b[1C";
    static constexpr const uint_fast8_t MOVE_ONE_SIZE = 4;
    static constexpr const char* COLOR_WHITE_BRIGHT = "\x1b[1;97m";
    static constexpr const char* COLOR_RED_BRIGHT = "\x1b[1;91m";
    static constexpr const uint_fast8_t COLOR_SIZE = 7;
    static constexpr const char* RESET_STYLE = "\x1b[0m";
    static constexpr const uint_fast8_t RESET_STYLE_SIZE = 4;
    uint_fast8_t column = 0;
    bool prompt = true;
    char line[COLUMNS] = {};

    void resetLine();
    void executeLineHandler();
    void executeTask(Task *task);
};

#endif //AVR_SHELL_H
