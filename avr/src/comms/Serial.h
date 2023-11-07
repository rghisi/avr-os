//
// Created by ghisi on 1/9/23.
//

#ifndef AVR_SERIAL_H
#define AVR_SERIAL_H


#include "../hw/USART.h"
#include "list"
#include "forward_list"
#include "../events/Subscriber.h"
#include "../collections/BlockingQueue.h"
#include "../system/Promise.h"

class Serial: public USARTInterruptHandler, public Subscriber {
public:
    explicit Serial(USART *usart);
    void readyToSend() override;
    void transmissionFinished() override;
    void frameReceived(uint8_t byte) override;

    void handle(Message *event) override;
    static void send(const char *bytes, size_t size);
    static void send(char *bytes, size_t size);
    static void send(size_t num);
    static void sendf(const char *format, size_t size, uintptr_t v);
    static Promise *sendAsync(char *bytes, size_t size);
    static Serial *self;

private:

    USART *usart;
};


#endif //AVR_SERIAL_H
