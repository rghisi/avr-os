//
// Created by ghisi on 09.11.22.
//

#ifndef AVR_ATMEGA328P_H
#define AVR_ATMEGA328P_H


#include "cstdint"
#include "../Timer0.h"
#include "../Interrupts.h"
#include "../I2C.h"
#include "../Timer1.h"
#include "../ExternalInterrupts.h"
#include "../USART.h"

extern "C" void USART_UDRE_vect(void) __attribute__ ((signal));
extern "C" void USART_TX_vect(void) __attribute__ ((signal));
extern "C" void USART_RX_vect(void) __attribute__ ((signal));
extern "C" void TIMER0_COMPA_vect(void) __attribute__ ((signal));
extern "C" void TIMER1_COMPA_vect(void) __attribute__ ((signal));
extern "C" void TIMER1_COMPB_vect(void) __attribute__ ((signal));
extern "C" void INT0_vect(void) __attribute__ ((signal));

class ATMega328P: public USART, public Interrupts, public Timer0, public Timer1, public ExternalInterrupt {
public:
    ATMega328P();
    void setupTimer0() override;
    void setTimer0InterruptHandler(Timer0InterruptHandler *handler) override;
    void setupTimer1() override;
    void resetTimer1() override;
    void startTimer1() override;
    void stopTimer1() override;
    uint16_t timer1Value() override;
    void timer1CompareMatchA(uint16_t value) override;
    void timer1CompareMatchB(uint16_t value) override;
    void setTimer1CompareMatchAInterruptHandler(TimerCompareMatchInterruptHandler *handler) override;
    void setTimer1CompareMatchBInterruptHandler(TimerCompareMatchInterruptHandler *handler) override;
    void timer1DoNothingOnCompareMatchA() override;
    void timer1ClearOnCompareMatchA() override;
    void timer1SetOnCompareMatchA() override;
    void timer1ForceCompareMatchA() override;
    void enableInterrupts() override;
    void disableInterrupts() override;
    void setupExternalInterrupt() override;
    void externalInterruptDisable() override;
    void externalInterruptOnFallingEdge() override;
    void externalInterruptOnRisingEdge() override;
    void setExternalInterruptHandler(ExternalInterruptHandler *handler) override;
    friend void USART_TX_vect(void);
    friend void USART_RX_vect(void);
    friend void USART_UDRE_vect(void);
    friend void TIMER0_COMPA_vect(void);
    friend void TIMER0_COMPA_vect(void);
    friend void TIMER1_COMPA_vect(void);
    friend void TIMER1_COMPB_vect(void);
    friend void INT0_vect(void);

    void disableReadyToSendInterrupt() override;
    void disableTransmitter() override;
    void enableTransmitterAndReadyToSendInterrupt() override;
    void enableReceiver() override;
    void disableReceiver() override;
    void setInterruptHandler(USARTInterruptHandler *handler) override;
    void send(uint8_t byte) override;

private:
    static USARTInterruptHandler *interruptHandler;
    static Timer0InterruptHandler *timer0InterruptHandler;
    static TimerCompareMatchInterruptHandler *timer1CompareMatchAInterruptHandler;
    static TimerCompareMatchInterruptHandler *timer1CompareMatchBInterruptHandler;
    static ExternalInterruptHandler *externalInterruptHandler;
};


#endif //AVR_ATMEGA328P_H
