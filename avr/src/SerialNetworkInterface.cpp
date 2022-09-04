/*
 * NetworkInterface.cpp
 *
 *  Created on: Aug 30, 2022
 *      Author: ghisi
 */

#include <avr/io.h>
#include "SerialNetworkInterface.h"
#include "BlockingQueue.cpp"

SerialNetworkInterface::SerialNetworkInterface(uint8_t networkAddress, USART *usart) {
    this->address = networkAddress;
    this->usart = usart;
    this->receiveQueue = new BlockingQueue<Packet>(QUEUE_SIZE);
    this->sendQueue = new BlockingQueue<Packet>(QUEUE_SIZE);
    this->rxState = IOState::IDLE;
    this->packetBeingSent = nullptr;
    this->packetBuilder = nullptr;
    toggleReceiver();
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

void SerialNetworkInterface::handleReadyToSendInterrupt() {
    if (packetBeingSent->hasNext() || prepareNextPacket()) {
        UDR1 = packetBeingSent->next();
    } else {
        usart->disableReadyToSendInterrupt();
    }
}

void SerialNetworkInterface::handleTransmissionFinished() {
    if (packetBeingSent == nullptr) {
        usart->disableTransmitter();
    }
}

void SerialNetworkInterface::handleDataReceivedInterrupt() {
    uint8_t receivedByte = UDR1;
    if (receivedByte == Packet::PACKET_START && packetBuilder == nullptr) {
        packetBuilder = new PacketBuilder();
        packetBuilder->add(receivedByte);
    } else {
        packetBuilder->add(receivedByte);
        if (packetBuilder->isFinished()) {
            auto *receivedPacket = packetBuilder->build();
            delete packetBuilder;
            packetBuilder = nullptr;
            receiveQueue->offer(receivedPacket);
        }
    }
}

void SerialNetworkInterface::toggleReceiver() {
    if (rxState == IOState::IDLE) {
        UCSR1B |= (1 << RXEN1) | (1 << RXCIE1);
        rxState = IOState::RUNNING;
    } else if (rxState == IOState::RUNNING) {
        UCSR1B &= ~((1 << RXEN1) | (1 << RXCIE1));
        rxState = IOState::IDLE;
    }
}