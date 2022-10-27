//
// Created by ghisi on 05.09.22.
//

#ifndef AVR_ATMEGA32U4_H
#define AVR_ATMEGA32U4_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../USART.h"
#include "../Timer0.h"

extern "C" void USART1_UDRE_vect(void) __attribute__ ((signal));
extern "C" void USART1_TX_vect(void) __attribute__ ((signal));
extern "C" void USART1_RX_vect(void) __attribute__ ((signal));
extern "C" void TIMER0_COMPA_vect(void) __attribute__ ((signal));

class ATMega32U4: public USART, public Timer0 {
public:
    enum class BitRate { B9600 };
    ATMega32U4(BitRate bitRate);
    void disableReadyToSendInterrupt() override;
    void disableTransmitter() override;
    void enableTransmitterAndReadyToSendInterrupt() override;
    void disableReceiver() override;
    void enableReceiver() override;
    void setInterruptHandler(USARTInterruptHandler *handler) override;
    void setTimer0InterruptHandler(Timer0InterruptHandler *handler) override;
    void send(uint8_t byte) override;
    friend void USART1_TX_vect(void);
    friend void USART1_RX_vect(void);
    friend void USART1_UDRE_vect(void);
    friend void TIMER0_COMPA_vect(void);
    inline static void txLedOn();
    inline static void txLedOff();
    inline static void rxLedOff();
    inline static void rxLedOn();
private:
    static USARTInterruptHandler *interruptHandler;
    static Timer0InterruptHandler *timer0InterruptHandler;
    static const uint8_t txLed = _BV(PORTD5);
    static const uint8_t rxLed = _BV(PORTB0);

};

#endif //AVR_ATMEGA32U4_H
