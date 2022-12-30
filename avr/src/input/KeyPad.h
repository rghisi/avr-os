//
// Created by ghisi on 30.10.22.
//

#ifndef AVR_KEYPAD_H
#define AVR_KEYPAD_H


#include "../system/Task.h"
#include "../system/EventDispatcher.h"

class KeyPad: public Task {
public:
    enum class Key { RELEASED, UP, DOWN, LEFT, RIGHT, ENTER };
    KeyPad(EventDispatcher *eventDispatcher);
    ~KeyPad() override = default;
    void run() override;
    uint32_t delay() override;
    Type type() override;
    void setup();
private:
    Key previous;
    EventDispatcher *eventDispatcher;
};


#endif //AVR_KEYPAD_H
