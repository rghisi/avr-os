//
// Created by ghisi on 1/9/23.
//

#ifndef AVR_SERIAL_H
#define AVR_SERIAL_H


#include "USART.h"
#include "../system/Promise.h"

class Serial {
public:
    explicit Serial(USART *usart);

    static void send(const char *bytes, size_t size);
    static void send(char *bytes, size_t size);
    static void send(char c);
    static void send(const char *text);
    static void send(size_t num);
    static Promise *sendAsync(char *bytes, size_t size);
    static Serial *self;
    static PromiseWithReturn<char> *readCharAsync();

private:
    USART *usart;
};


#endif //AVR_SERIAL_H
