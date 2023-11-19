//
// Created by ghisi on 1/9/23.
//

#ifndef AVR_SERIAL_H
#define AVR_SERIAL_H


#include "../hw/USART.h"
#include "../system/Promise.h"

class Serial {
public:
    explicit Serial(USART *usart);

    static void send(const char *bytes, size_t size);
    static void send(char *bytes, size_t size);
    static void send(char c);
    static void send(size_t num);
    static void sendf(const char *format, size_t size, uintptr_t v);
    static Promise *sendAsync(char *bytes, size_t size);
    static Serial *self;
    static PromiseWithReturn<char> *readCharAsync();

private:

    USART *usart;
};


#endif //AVR_SERIAL_H
