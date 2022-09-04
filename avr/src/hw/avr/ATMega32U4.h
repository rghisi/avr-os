//
// Created by ghisi on 05.09.22.
//

#ifndef AVR_ATMEGA32U4_H
#define AVR_ATMEGA32U4_H

#include "../../USART.h"

class ATMega32U4: public USART {
public:
    void disableReadyToSendInterrupt() override;
    void disableTransmitter() override;
    void enableTransmitterAndReadyToSendInterrupt() override;
};


#endif //AVR_ATMEGA32U4_H
