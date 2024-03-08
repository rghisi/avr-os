//
// Created by ghisi on 19.11.23.
//

#ifndef AVR_LIST_H
#define AVR_LIST_H

#include "../Shell.h"
#include "../ShellCommand.h"

class List: public ShellCommand {
public:
    explicit List(Shell *shell) : ShellCommand("ls") {
        this->shell = shell;
    }

    void run(char* args) override {
        for (auto &command: shell->commands) {
            Serial::send(command->name, strlen(command->name));
            Serial::send("\t", 1);
        }
        for (auto &app: shell->apps) {
            Serial::send(app->name, strlen(app->name));
            Serial::send("\t", 1);
        }
        Serial::send("\r\n", 2);
    }

private:
    Shell *shell;
};
#endif //AVR_LIST_H
