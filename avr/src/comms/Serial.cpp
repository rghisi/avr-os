//
// Created by ghisi on 1/9/23.
//

#include "Serial.h"
#include "cstdio"
#include "cstring"

Serial::Serial(USART *usart) {
    this->usart = usart;
}

void Serial::send(const char *text) {
    Serial::self->usart->enableTransmitter();
    size_t i = 0;
    while (text[i] != 0) {
        Serial::self->usart->send(text[i]);
        i++;
    }
    Serial::self->usart->disableTransmitter();
}

void Serial::send(const uint8_t *bytes, size_t size) {
    Serial::self->usart->enableTransmitter();
    for (size_t i = 0; i < size; i++) {
        Serial::self->usart->send(bytes[i]);
    }
    Serial::self->usart->disableTransmitter();
}

Promise *Serial::sendAsync(uint8_t *bytes, size_t size) {
    Serial::self->usart->enableTransmitter();
    for (size_t i = 0; i < size; i++) {
        Serial::self->usart->send(bytes[i]);
    }
    Serial::self->usart->disableTransmitter();
    auto promise = new Promise();
    promise->complete();
    return promise;
}

void Serial::send(size_t num) {
    Serial::self->usart->enableTransmitter();
    auto buffer = new char[10];
    sprintf(buffer, "%u", num);
    auto len = strlen(buffer);
    for (size_t i = 0; i < len; i++) {
        Serial::self->usart->send(buffer[i]);
    }
    delete[] buffer;
    Serial::self->usart->disableTransmitter();
}

PromiseWithReturn<char> *Serial::readCharAsync() {
    auto promise = new PromiseWithReturn<char>();
    promise->data = 0;
    self->usart->readCharAsync(promise);
    return promise;
}

void Serial::send(char c) {
    Serial::self->usart->enableTransmitter();
    Serial::self->usart->send(c);
    Serial::self->usart->disableTransmitter();
}
