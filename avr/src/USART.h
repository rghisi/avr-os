//
// Created by ghisi on 05.09.22.
//

#ifndef AVR_USART_H
#define AVR_USART_H

class USART {
public:
    virtual void disableReadyToSendInterrupt() = 0;
    virtual void disableTransmitter() = 0;
    virtual void enableTransmitterAndReadyToSendInterrupt() = 0;
};

#endif //AVR_USART_H
