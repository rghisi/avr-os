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
	void setup();

    ~Dial() override = default;

    void run() override;

    uint32_t delay() override;

    Type type() override;

private:
	void calculateDialIncrement();
    EventDispatcher *eventDispatcher;
	uint8_t inputPinValues;
	uint8_t pushButtonValue;
	uint8_t newPushButtonValue;
	uint8_t newDialValue;
	uint8_t dialValue;
	int8_t dialIncrement;

	static const uint8_t DIAL_PORT_MASK = _BV(PORTC5) | _BV(PORTC4) | _BV(PORTC3);
	static const uint8_t DIAL_A_PORT = PORTC3;
	static const uint8_t DIAL_B_PORT = PORTC4;
	static const uint8_t PUSH_BUTTON_PORT = PORTC5;
	static const int8_t QUADRATURE_TABLE[];

};

#endif /* INPUT_DIAL_H_ */
