//
// Created by ghisi on 05.09.22.
//

#ifndef AVR_USART_H
#define AVR_USART_H

class USARTInterruptHandler {
public:
    virtual void readyToSend() = 0;
    virtual void transmissionFinished() = 0;
    virtual void dataReceived(uint8_t byte) = 0;
};

class USART {
public:
    virtual void disableReadyToSendInterrupt() = 0;
    virtual void disableTransmitter() = 0;
    virtual void enableTransmitterAndReadyToSendInterrupt() = 0;
    virtual void enableReceiver() = 0;
    virtual void disableReceiver() = 0;
    virtual void setInterruptHandler(USARTInterruptHandler *handler) = 0;
    virtual void send(uint8_t byte) = 0;
};

#endif //AVR_USART_H
