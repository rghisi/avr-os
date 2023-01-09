//
// Created by ghisi on 1/9/23.
//

#include "Serial.h"
#include "SerialPacket.h"

Serial::Serial(USART *usart) {
    this->usart = usart;
}

void Serial::readyToSend() {
    if (outputBuffer.isEmpty()) {
        usart->disableReadyToSendInterrupt();
    } else {
        usart->send(outputBuffer.poll());
    }
}

void Serial::transmissionFinished() {
    if (outputBuffer.isEmpty()) {
        usart->disableTransmitter();
    }
}

void Serial::frameReceived(uint8_t byte) {

}

void Serial::handle(Message *event) {
    if (event->type() == MessageType::SERIAL_SEND) {
        auto serialPacket = static_cast<SerialPacket*>(event);
        for (uint8_t i = 0; i < serialPacket->length; i++) {
            outputBuffer.offer(serialPacket->bytes[i]);
        }
        usart->enableTransmitterAndReadyToSendInterrupt();
    }
}
