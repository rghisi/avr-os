/*
 * Dial.h
 *
 *  Created on: Dec 29, 2020
 *      Author: ghisi
 */

#ifndef INPUT_DIAL_H_
#include <avr/io.h>
#include "../system/EventDispatcher.h"
#include "../system/Task.h"

#define INPUT_DIAL_H_

class Dial: public Task {
public:
	Dial(EventDispatcher *eventDispatcher);
    ~Dial() override = default;
    void setup();
    void run() override;
    uint32_t delay() override;
    Type type() override;

private:
    static constexpr uint8_t DIAL_PLUS = 0b00000010;
    static constexpr uint8_t DIAL_MINUS = 0b00000001;
    static constexpr uint8_t DIAL_IDLE = 0;
    static const uint8_t DIAL_A_PORT = PORTC1;
    static const uint8_t DIAL_B_PORT = PORTC2;
    static const uint8_t PUSH_BUTTON_PORT = PORTC3;
    static const uint8_t DIAL_PORT_MASK = _BV(DIAL_A_PORT) | _BV(DIAL_B_PORT) | _BV(PUSH_BUTTON_PORT);

    EventDispatcher *eventDispatcher;
    uint8_t lastDialReadout;
    bool lastPushButtonState;
//    static const int8_t QUADRATURE_TABLE[];

};

#endif /* INPUT_DIAL_H_ */
