//
// Created by ghisi on 08.11.23.
//

#ifndef AVR_CONSOLE_H
#define AVR_CONSOLE_H

#include "../system/HeapTask.h"
#include "../comms/Serial.h"

class Console: public HeapTask {
public:
    Console();
    void run() override;
};

Console::Console() : HeapTask(128) {

}

void Console::run() {
    while (true) {
        auto line = Serial::readLine();
//        sleep(200);
        Serial::send(line, strlen(line));
//        if (line->starts_with("pi")) {
//            Serial::send("aqui\n", 5);
//            auto piTask = new PiTask();
//            await(OS::execAsync(piTask));
//        } else if (line->starts_with("bu")) {
//            auto task = new BuTask();
//            await(OS::execAsync(task));
//        }
        delete line;
        auto task = new PiTask();
        await(OS::execAsync(task));
        delete task;
    }
}


#endif //AVR_CONSOLE_H
