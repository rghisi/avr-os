//
// Created by ghisi on 1/9/23.
//

#include "Serial.h"
#include "SerialPacket.h"
#include "cstdio"
#include "cstring"
#include "../system/PromiseWithReturn.h"

Serial::Serial(USART *usart) {
    this->usart = usart;
}

void Serial::readyToSend() {

}

void Serial::transmissionFinished() {

}

void Serial::frameReceived(uint8_t byte) {

}

void Serial::handle(Message *event) {
    if (event->type() == MessageType::SERIAL_SEND) {
        auto serialPacket = static_cast<SerialPacket*>(event);
        for (uint8_t i = 0; i < serialPacket->length; i++) {
            usart->send(serialPacket->bytes[i]);
        }
    }
}

void Serial::send(const char *bytes, size_t size) {
    for (size_t i = 0; i < size; i++) {
        Serial::self->usart->send(bytes[i]);
    }
}

void Serial::sendf(const char *format, size_t size, uintptr_t ptr) {
    auto buffer = new char[size];
    sprintf(buffer, format, ptr);
    auto len = strlen(buffer);
    for (size_t i = 0; i < len; i++) {
        Serial::self->usart->send(buffer[i]);
    }
}

void Serial::send(char *bytes, size_t size) {
    for (size_t i = 0; i < size; i++) {
        Serial::self->usart->send(bytes[i]);
    }

    delete[] bytes;
}

Promise *Serial::sendAsync(char *bytes, size_t size) {
    for (size_t i = 0; i < size; i++) {
        Serial::self->usart->send(bytes[i]);
    }
    delete[] bytes;
    auto promise = new Promise();
    promise->complete();
    return promise;
}

void Serial::send(size_t num) {
    auto buffer = new char[10];
    sprintf(buffer, "%u\n", num);
    auto len = strlen(buffer);
    for (size_t i = 0; i < len; i++) {
        Serial::self->usart->send(buffer[i]);
    }
    delete[] buffer;
}

char *Serial::readLine() {
    return Serial::self->usart->readLine();
}

Promise *Serial::readLineAsync() {
    auto promise = new PromiseWithReturn<char*>();
    self->usart->readLine(promise);
    return promise;
}
