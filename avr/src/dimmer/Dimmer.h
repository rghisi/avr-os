//
// Created by ghisi on 20.11.22.
//

#ifndef AVR_DIMMER_H
#define AVR_DIMMER_H


#include "../hw/ExternalInterrupts.h"
#include "../hw/Timer1.h"

class Dimmer: public ExternalInterruptHandler, public TimerCompareMatchInterruptHandler {
public:
    explicit Dimmer(Timer1 *timer1, ExternalInterrupt *externalInterrupt);
    void handleExternalInterrupt() override;
    void setPosition(uint16_t position);
    uint16_t getPosition();
    void enable();
    void disable();

private:
    static constexpr uint16_t PULSE_LENGTH = 1200;
    static constexpr uint16_t HEADROOM = 500;
    static constexpr uint16_t MAX_DELAY = 16666 - HEADROOM;
    void handleTimerCompareMatchInterrupt() override;
    enum class State: uint8_t {
        DISABLED,
        WAITING_ZERO_CROSS_START,
        WAITING_PULSE_START,
        WAITING_PULSE_END,
    };
    State state = State::DISABLED;
    Timer1 *timer;
    ExternalInterrupt *externalInterrupt;
    uint16_t timeToZeroCross = 1200;
    uint16_t delay = MAX_DELAY;
};


#endif //AVR_DIMMER_H
