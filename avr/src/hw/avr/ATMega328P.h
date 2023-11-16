//
// Created by ghisi on 09.11.22.
//

#ifndef AVR_ATMEGA328P_H
#define AVR_ATMEGA328P_H


#include "cstdint"
#include "../USART.h"
#include "vector"

extern "C" void USART_UDRE_vect(void) __attribute__ ((signal));
extern "C" void USART_TX_vect(void) __attribute__ ((signal));
extern "C" void USART_RX_vect(void) __attribute__ ((signal));
extern "C" void TIMER1_COMPA_vect(void) __attribute__ ((signal));
extern "C" void TIMER1_COMPB_vect(void) __attribute__ ((signal));
extern "C" void INT0_vect(void) __attribute__ ((signal));

class ATMega328P: public USART {
public:
    ATMega328P();
    friend void USART_TX_vect(void);
    friend void USART_RX_vect(void);
    friend void USART_UDRE_vect(void);

    void disableReadyToSendInterrupt() override;
    void disableTransmitter() override;
    void enableTransmitter() override;
    void enableReceiver() override;
    void disableReceiver() override;
    void setInterruptHandler(USARTInterruptHandler *handler) override;
    void send(uint8_t byte) override;
    char *readLine() override;
    void readLine(PromiseWithReturn<char*> *promise) override;

private:
    static USARTInterruptHandler *interruptHandler;
};


#endif //AVR_ATMEGA328P_H
