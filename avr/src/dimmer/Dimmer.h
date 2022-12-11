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
    void setPosition(uint8_t position);
    void calibrate();
    void enable();
    void disable();

private:
    static constexpr int PULSE_LENGTH = 50;
    void handleTimerCompareMatchInterrupt() override;
    enum class State {
        UNINITIALIZED,
        CALIBRATING_WAITING_ZERO_CROSS_START,
        CALIBRATING_WAITING_ZERO_CROSS_END,
        CALIBRATING_WAITING_HALF_WAVE_END,
        DISABLED,
        WAITING_ZERO_CROSS_START,
        WAITING_PULSE_START,
        WAITING_PULSE_END,
        PULSE_ENDED
    };
    State state = State::UNINITIALIZED;
    Timer1 *timer;
    ExternalInterrupt *externalInterrupt;
    uint16_t timeToZeroCross = 0;
    uint16_t halfWaveLength = 0;
    uint16_t positionStep = 0;
    uint16_t position = 0;
    void processState();
};


#endif //AVR_DIMMER_H
