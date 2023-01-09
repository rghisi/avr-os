//
// Created by ghisi on 1/9/23.
//

#ifndef AVR_SERIAL_H
#define AVR_SERIAL_H


#include "../hw/USART.h"
#include "list"
#include "forward_list"
#include "../system/Subscriber.h"
#include "../collections/BlockingQueue.cpp"

class Serial: public USARTInterruptHandler, public Subscriber {
public:
    explicit Serial(USART *usart);
    void readyToSend() override;
    void transmissionFinished() override;
    void frameReceived(uint8_t byte) override;

    void handle(Message *event) override;

private:
    BlockingQueue<uint8_t, 30> outputBuffer;
    USART *usart;
};


#endif //AVR_SERIAL_H
