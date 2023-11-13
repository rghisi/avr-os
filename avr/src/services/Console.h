//
// Created by ghisi on 08.11.23.
//

#ifndef AVR_CONSOLE_H
#define AVR_CONSOLE_H

#include "../comms/Serial.h"

class Console: public Task {
public:
    Console();
    void run() override;
};

Console::Console() : Task(new HeapStack(128)) {

}

void Console::run() {
    while (true) {
        auto promise = static_cast<PromiseWithReturn<char*>*>(await(Serial::readLineAsync()));
//        sleep(500);
//        Serial::send(promise->data, strlen(promise->data));
//        if (line->starts_with("pi")) {
//            Serial::send("aqui\n", 5);
//            auto piTask = new PiTask();
//            await(OS::execAsync(piTask));
//        } else if (line->starts_with("bu")) {
//            auto task = new BuTask();
//            await(OS::execAsync(task));
//        }
//        delete promise->data;
        delete promise;
        auto task = new PiTask();
        auto p = await(OS::execAsync(task));
        delete p;
        delete task;
    }
}


#endif //AVR_CONSOLE_H
