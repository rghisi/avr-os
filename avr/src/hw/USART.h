//
// Created by ghisi on 05.09.22.
//

#ifndef AVR_USART_H
#define AVR_USART_H

#include "cstdint"
#include "string_view"
#include "vector"
#include "../system/Promise.h"
#include "../system/PromiseWithReturn.h"

class USARTInterruptHandler {
public:
    virtual void readyToSend() = 0;
    virtual void transmissionFinished() = 0;
    virtual void frameReceived(uint8_t byte) = 0;
};

class USART {
public:
    virtual void disableReadyToSendInterrupt() = 0;
    virtual void disableTransmitter() = 0;
    virtual void enableTransmitter() = 0;
    virtual void enableReceiver() = 0;
    virtual void disableReceiver() = 0;
    virtual void setInterruptHandler(USARTInterruptHandler *handler) = 0;
    virtual void send(uint8_t byte) = 0;
    virtual char *readLine() = 0;
    virtual void readLine(PromiseWithReturn<char*> *promise) = 0;
};

#endif //AVR_USART_H
