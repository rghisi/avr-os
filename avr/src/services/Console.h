//
// Created by ghisi on 08.11.23.
//

#ifndef AVR_CONSOLE_H
#define AVR_CONSOLE_H

#include "../comms/Serial.h"
#include "functional"
#include "BuTask.h"

class Console: public Task {
public:
    Console();

    [[noreturn]] void run() override;
private:
    static constexpr uint_fast8_t COLUMNS = 40;
    static constexpr uint_fast8_t FIRST = 0;
    static constexpr uint_fast8_t LAST = COLUMNS - 1;
    static constexpr char BACKSPACE = '\b';
    static constexpr char CARRIAGE_RETURN = '\r';
    static constexpr char LINE_FEED = '\n';
    static constexpr const char* ERASE = "\x1b[J";
    static constexpr const uint_fast8_t ERASE_SIZE = 3;
    static constexpr const char* CLEAR_SCREEN = "\x1b[2J\x1b[H";
    static constexpr const uint_fast8_t CLEAR_SCREEN_SIZE = 7;
    uint_fast8_t column = 0;
    char line[COLUMNS] = {};
    std::array<const char*, 5> commands = {"ls", "clear", "pi", "free", "bu"};
    std::array<std::function<void(void)>, 5> invokers = {
            [&]() { list();},
            [&]() { Serial::send(CLEAR_SCREEN, CLEAR_SCREEN_SIZE);},
            [this]() { executeTask(new PiTask()); },
            [this]() { executeTask(new PerformanceReporter()); },
            [this]() { executeTask(new BuTask()); }
    };

    void resetLine();
    void executeLineHandler();
    void list();
    void executeTask(Task *task);
};

Console::Console() : Task(new HeapStack(128)) {
}

[[noreturn]] void Console::run() {
    while (true) {
        if (column == FIRST) {
            Serial::send("\x1b[1;92m#\x1b[0m ", 13);
        }
        auto promise = static_cast<PromiseWithReturn<char>*>(await(Serial::readCharAsync()));
        auto character = promise->data;
        Serial::send(character);
        switch (character) {
            case BACKSPACE:
                if (column > 0) {
                    line[--column] = 0;
                    Serial::send(ERASE, ERASE_SIZE);
                }
                break;
            case CARRIAGE_RETURN:
                Serial::send(LINE_FEED);
                executeLineHandler();
                resetLine();
                break;
            default:
                if (column == LAST) {
                    Serial::send(LINE_FEED);
                    resetLine();
                } else {
                    line[column++] = character;
                }
                break;
        }



        delete promise;
    }
}

void Console::resetLine() {
    for (char &character : line) {
        character = 0;
    }
    column = 0;
}

void Console::executeLineHandler() {
    if (column == 0) {
        return;
    }

    auto cpr = [&](const char* command) -> bool {
        return strcmp(command, (const char*)line) == 0;
    };
    auto found = std::find_if(commands.begin(), commands.end(), cpr);
    if (found != std::end(commands)) {
        auto index = found - commands.begin();
        invokers[index]();
    } else {
        Serial::send("404\r\n", 5);
    }
}

void Console::list() {
    for (auto &command : commands) {
        Serial::send(command, strlen(command));
        Serial::send("\r\n", 2);
    }
}

void Console::executeTask(Task *task) {
    auto promise = await(OS::execAsync(task));
    delete promise;
    delete task;
}

#endif //AVR_CONSOLE_H
