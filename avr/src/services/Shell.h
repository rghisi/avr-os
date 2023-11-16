//
// Created by ghisi on 16.11.23.
//

#ifndef AVR_SHELL_H
#define AVR_SHELL_H

#include "ConsoleLineHandler.h"
#include "functional"

class Shell: public ConsoleLineHandler {
public:
    Shell();
    void handle(char *line) override;
    void addCommand(const char *name, const std::function<void(void)>& func);
    void list();
private:
    std::vector<const char*> commands = std::vector<const char*>();
    std::vector<std::function<void(void)>> invokers = std::vector<std::function<void(void)>>();
};

Shell::Shell() {
    addCommand("ls", [&]() { list();});
//    addCommand("pi", [this]() {
//        auto task = new PiTask();
//        auto promise = await(OS::execAsync(task));
//    });
}

void Shell::handle(char *line) {
    auto cpr = [&](const char* command) -> bool {
        return strcmp(command, (const char*)line) == 0;
    };
    auto found = std::find_if(commands.begin(), commands.end(), cpr);
    if (found != std::end(commands)) {
        auto index = found - commands.begin();
        invokers[index]();
        Serial::send("200\r\n", 5);
    } else {
        Serial::send("404\r\n", 5);
    }
}

void Shell::addCommand(const char *name, const std::function<void(void)>& func) {
    commands.push_back(name);
    invokers.push_back(func);
}

void Shell::list() {
    Serial::send("list!\r\n", 7);
}

#endif //AVR_SHELL_H
