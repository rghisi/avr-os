//
// Created by ghisi on 19.11.23.
//

#include "console/Shell.h"
#include "system/OS.h"
#include "console/App.h"
#include "system/HeapStack.h"
#include "apps/PiTask.h"
#include "apps/PerformanceReporter.h"
#include "console/commands/List.h"
#include "apps/BuTask.h"
#include "algorithm"
#include "console/commands/Clear.h"

Shell::Shell() : Task(new HeapStack(128)) {
   apps = {new PiApp(), new FreeApp(), new BuApp()};
   commands = {new List(this), new Clear()};
}

[[noreturn]] void Shell::run() {
    while (true) {
        if (column == FIRST && prompt) {
            Serial::send("\x1b[1;92m#\x1b[0m ", 13);
            prompt = false;
        }
        auto promise = static_cast<PromiseWithReturn<char>*>(await(Serial::readCharAsync()));
        auto character = promise->data;
        delete promise;
        Serial::send(character);
        switch (character) {
            case BACKSPACE:
                if (column > 0) {
                    line[--column] = 0;
                    Serial::send(ERASE, ERASE_SIZE);
                } else {
                    Serial::send(MOVE_ONE_RIGHT, MOVE_ONE_SIZE);
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
    }
}

void Shell::resetLine() {
    for (char &character : line) {
        character = 0;
    }
    column = 0;
    prompt = true;
}

void Shell::executeLineHandler() {
    if (column == 0) {
        return;
    }

    auto appNameMatcher = [&](App *app) -> bool {
        return strcmp(app->name, (const char*)line) == 0;
    };

    auto found = std::find_if(apps.begin(), apps.end(), appNameMatcher);

    if (found != std::end(apps)) {
        auto index = found - apps.begin();
        executeTask(apps[index]->load());
    } else {
        auto commandNameMatcher = [&](ShellCommand *command) -> bool {
            return strcmp(command->name, (const char*)line) == 0;
        };
        auto commandFound = std::find_if(commands.begin(), commands.end(), commandNameMatcher);
        if (commandFound != std::end(commands)) {
            auto index = commandFound - commands.begin();
            commands[index]->run();
        } else {
            Serial::send(COLOR_WHITE_BRIGHT, COLOR_SIZE);
            Serial::send(line, column + 1);
            Serial::send(COLOR_RED_BRIGHT, COLOR_SIZE);
            Serial::send(" NOT FOUND\r\n", 11);
            Serial::send(RESET_STYLE, RESET_STYLE_SIZE);
        }
    }
}

void Shell::executeTask(Task *task) {
    auto promise = await(OS::execAsync(task));
    delete promise;
}