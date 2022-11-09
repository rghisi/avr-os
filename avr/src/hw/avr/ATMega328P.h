//
// Created by ghisi on 09.11.22.
//

#ifndef AVR_ATMEGA328P_H
#define AVR_ATMEGA328P_H


#include "../Timer0.h"
#include "../USART.h"
#include "cstdint"
#include "../Interrupts.h"

class ATMega328P: public Interrupts, public USART, public Timer0 {
public:
    void setTimer0InterruptHandler(Timer0InterruptHandler *handler) override;

    void disableReadyToSendInterrupt() override;

    void disableTransmitter() override;

    void enableTransmitterAndReadyToSendInterrupt() override;

    void enableReceiver() override;

    void disableReceiver() override;

    void setInterruptHandler(USARTInterruptHandler *handler) override;

    void send(uint8_t byte) override;

    void enableInterrupts() override;

    void disableInterrupts() override;

};


#endif //AVR_ATMEGA328P_H
