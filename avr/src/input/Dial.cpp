/*
 * Dial.cpp
 *
 *  Created on: Dec 29, 2020
 *      Author: ghisi
 */

#include "Dial.h"
#include "UserInput.h"
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
    lastDialReadout = 0x00;
    lastPushButtonState = false;
}

void Dial::setup() {
	DDRC &= ~DIAL_PORT_MASK;
	PORTC |= DIAL_PORT_MASK;
}

void Dial::run() {
	auto inputPinValues = ~(PINC & DIAL_PORT_MASK);
	auto newPushButtonState = (bool)((inputPinValues >> PUSH_BUTTON_PORT) & 0x01);
	auto newDialReadout = (inputPinValues >> DIAL_A_PORT) & 0b00000011;

    if (newPushButtonState != lastPushButtonState) {
        std::unique_ptr<Event> event;
        if (newPushButtonState) {
            event = std::make_unique<Event>(Event(USER_INPUT, new UserInput(UserInput::Event::DIAL_BUTTON_PRESSED, 0x00)));
        } else {
            event = std::make_unique<Event>(Event(USER_INPUT, new UserInput(UserInput::Event::DIAL_BUTTON_RELEASED, 0x00)));
        }
        eventDispatcher->dispatch(std::move(event));
        lastPushButtonState = newPushButtonState;
    }
	if (newDialReadout != lastDialReadout) {
        if (lastDialReadout == DIAL_IDLE) {
            std::unique_ptr<Event> event;
            switch (newDialReadout) {
                case DIAL_PLUS:
                    event = std::make_unique<Event>(Event(USER_INPUT, new UserInput(UserInput::Event::DIAL_PLUS, 0x00)));
                    eventDispatcher->dispatch(std::move(event));
                    break;
                case DIAL_MINUS:
                    event = std::make_unique<Event>(Event(USER_INPUT, new UserInput(UserInput::Event::DIAL_MINUS, 0x00)));
                    eventDispatcher->dispatch(std::move(event));
                    break;
                default:
                    break;
            }
        }
        lastDialReadout = newDialReadout;
	}
}

uint32_t Dial::delay() {
    return 1;
}

Task::Type Dial::type() {
    return Type::PERIODIC;
}
