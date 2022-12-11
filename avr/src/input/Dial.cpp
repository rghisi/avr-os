/*
 * Dial.cpp
 *
 *  Created on: Dec 29, 2020
 *      Author: ghisi
 */

#include "Dial.h"
//Full - 4 ticks per click
//static const int8_t Dial::QUADRATURE_TABLE[] = { 0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1 };
//Partial - 1 tick per click
//static const int8_t Dial::QUADRATURE_TABLE[] = { 0,  0, 0, 0, 0, 0, 0, -1,  0, 0, 0, 1, 0, 0,  0 };
/*
 * Period = 1ms
 * 0 0 = idle state
 * 1 0 = right turn (+1)
 * 0 1 = left turn (-1)
 */
Dial::Dial(EventDispatcher *eventDispatcher) {
	this->eventDispatcher = eventDispatcher;
	inputPinValues = 0;
	pushButtonValue = 0;
	newPushButtonValue = 0;
	dialValue = 0;
	newDialValue = 0;
	dialIncrement = 0;
}

void Dial::setup() {
	DDRC &= !DIAL_PORT_MASK;
	PORTC |= DIAL_PORT_MASK;
	inputPinValues = PINC & DIAL_PORT_MASK;
	pushButtonValue = (inputPinValues >> PUSH_BUTTON_PORT) & 0x00000001b;
	dialValue = (inputPinValues >> DIAL_B_PORT) & 0x00000011b;
}

void Dial::run() {
	inputPinValues = PINC & DIAL_PORT_MASK;
	newPushButtonValue = (inputPinValues >> PUSH_BUTTON_PORT) & 0x01;
	newDialValue = (inputPinValues >> DIAL_A_PORT) & 0x03;

	if (newDialValue != dialValue) {
		calculateDialIncrement();
		if (dialIncrement == 1) {
//			inputHandler->Enqueue(InputEvent::dialPlus);
		} else if (dialIncrement == -1) {
//			inputHandler->Enqueue(InputEvent::dialMinus);
		}
	}


	if (pushButtonValue != newPushButtonValue) {
		pushButtonValue = newPushButtonValue;
		if (pushButtonValue == 1) {
//			inputHandler->Enqueue(InputEvent::dialPushButtonReleased);
		} else {
//			inputHandler->Enqueue(InputEvent::dialPushButtonPressed);
		}
	}
}

void Dial::calculateDialIncrement() {
	dialIncrement = QUADRATURE_TABLE[(newDialValue << 2) + dialValue];
	dialValue = newDialValue;
}

uint32_t Dial::delay() {
    return 1;
}

Task::Type Dial::type() {
    return Type::PERIODIC;
}
