/*
 * NetworkInterface.cpp
 *
 *  Created on: Aug 30, 2022
 *      Author: ghisi
 */
#include <avr/io.h>
#include <util/delay.h>

#include "SerialNetworkInterface.h"
#include "../collections/BlockingQueue.cpp"
#include "../std/Random.h"

SerialNetworkInterface::SerialNetworkInterface(uint8_t networkAddress, USART *usart) {
    this->address = networkAddress;
    this->usart = usart;
    this->receiveQueue = new BlockingQueue<Packet*>(QUEUE_SIZE);
    this->sendQueue = new BlockingQueue<Packet*>(QUEUE_SIZE);
    this->sentBytes = new BlockingQueue<uint8_t>(2);
    this->packetBeingSent = nullptr;
    this->packetBuilder = nullptr;
    this->isTransmitting = false;
    usart->enableReceiver();
}

SerialNetworkInterface::~SerialNetworkInterface() {
    delete receiveQueue;
    delete sendQueue;
}

Packet *SerialNetworkInterface::popFromReceiveQueue() {
    return this->receiveQueue->poll();
}

bool SerialNetworkInterface::pushToSendQueue(Packet *packet) {
    if (packetBeingSent == nullptr) {
        packetBeingSent = packet;
        usart->enableTransmitterAndReadyToSendInterrupt();
        isTransmitting = true;
        sentBytes->clear();
        return true;
    } else {
        return sendQueue->offer(packet);
    }
}

bool SerialNetworkInterface::acceptsPacket() {
    return !sendQueue->isFull();
}

bool SerialNetworkInterface::receiveQueueHasPackets() {
    return !receiveQueue->isEmpty();
}

bool SerialNetworkInterface::prepareNextPacket() {
    delete packetBeingSent;
    packetBeingSent = sendQueue->poll();

    return packetBeingSent != nullptr;
}

inline void SerialNetworkInterface::transmissionFinished() {
    if (packetBeingSent == nullptr) {
        usart->disableTransmitter();
        isTransmitting = false;
    }
}

inline void SerialNetworkInterface::readyToSend() {
    if (packetBeingSent->hasNext() || prepareNextPacket()) {
        uint8_t byteToSend = packetBeingSent->next();
        usart->send(byteToSend);
        sentBytes->offer(byteToSend);
    } else {
        usart->disableReadyToSendInterrupt();
    }
}

inline void SerialNetworkInterface::dataReceived(uint8_t receivedByte) {
    if (isTransmitting) {
//        auto transmitted = sentBytes->poll();
//        if (receivedByte != transmitted) {
//            backoffAndRetry();
//        }
    } else {
        if (receivedByte == Packet::PACKET_START && packetBuilder == nullptr) {
            UDR1 = 's';
            packetBuilder = new PacketBuilder();
            packetBuilder->add(receivedByte);
        } else if (packetBuilder != nullptr) {
            UDR1 = '+';
            packetBuilder->add(receivedByte);
            if (packetBuilder->isFinished()) {
                auto *receivedPacket = packetBuilder->build();
                if (receivedPacket->checkCrc()) {
                    UDR1 = 'c';
//                    _delay_ms(100);
//                    receiveQueue->offer(receivedPacket);
                } else {
                    UDR1 = 'f';
//                    _delay_ms(100);
                }
                delete packetBuilder;
                packetBuilder = nullptr;
            }
        }
    }
}

void SerialNetworkInterface::backoffAndRetry() {
    usart->disableReadyToSendInterrupt();
    usart->disableTransmitter();
    packetBeingSent->reset();
    sentBytes->clear();
    _delay_loop_1(Random::next());

    PORTB ^= 0xFF;
    _delay_ms(500);
    PORTB ^= 0xFF;
    _delay_ms(500);
    PORTB ^= 0xFF;
    _delay_ms(500);
    PORTB ^= 0xFF;
    _delay_ms(500);
    PORTB ^= 0xFF;
    _delay_ms(500);
    PORTB ^= 0xFF;
    _delay_ms(500);
    PORTB ^= 0xFF;
}

uint8_t SerialNetworkInterface::getAddress() {
    return address;
}
