/*
 * NetworkInterface.cpp
 *
 *  Created on: Aug 30, 2022
 *      Author: ghisi
 */

#include <avr/io.h>
#include "SerialNetworkInterface.h"
#include "BlockingQueue.cpp"

SerialNetworkInterface::SerialNetworkInterface(uint8_t networkAddress) {
    address = networkAddress;
    receiveQueue = new BlockingQueue<Packet>(QUEUE_SIZE);
    sendQueue = new BlockingQueue<Packet>(QUEUE_SIZE);
    txState = IOState::IDLE;
    txDataState = DataState::WAITING_DATA;
    rxState = IOState::IDLE;
    rxDataState = DataState::WAITING_DATA;
    packetBeingSent = nullptr;
    packetBuilder = nullptr;
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
        preparePacketToSend();
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

void SerialNetworkInterface::preparePacketToSend() {
    if (packetBeingSent == nullptr && !sendQueue->isEmpty()) {
        packetBeingSent = sendQueue->poll();
    }
    if (packetBeingSent != nullptr) {
        if (packetBeingSent->hasNext()) {
            txDataState = DataState::DATA_READY;
        } else {
            delete packetBeingSent;
            if (!sendQueue->isEmpty()) {
                packetBeingSent = sendQueue->poll();
            } else {
                packetBeingSent = nullptr;
                txDataState = DataState::WAITING_DATA;
            }
        }
    }
    toggleTransmitter();
}

uint8_t SerialNetworkInterface::nextByteToSend() {
    preparePacketToSend();
    return packetBeingSent->next();
}

void SerialNetworkInterface::handleReadyToSendInterrupt() {
    if (txDataState == DataState::DATA_READY) {
        UDR1 = nextByteToSend();
    } else {
        toggleTransmitter();
    }
}

void SerialNetworkInterface::handleTransmissionFinished() {
    if (txDataState == DataState::WAITING_DATA) {
        toggleTransmitter();
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
            auto* receivedPacket = packetBuilder->build();
            delete packetBuilder;
            packetBuilder = nullptr;
            receiveQueue->offer(receivedPacket);
        }
    }
}

void SerialNetworkInterface::toggleTransmitter() {
    if (txDataState == DataState::DATA_READY && (txState == IOState::IDLE || txState == IOState::FINALIZING)) {
        UCSR1B |= (1 << TXEN1) | (1 << UDRIE1);
        txState = IOState::RUNNING;
    } else if (txDataState == DataState::WAITING_DATA && txState == IOState::RUNNING) {
        UCSR1B &= ~(1 << UDRIE1);
        txState = IOState::FINALIZING;
    } else if (txDataState == DataState::WAITING_DATA && txState == IOState::FINALIZING) {
//        UCSR1B &= ~(1 << TXEN1);
        txState = IOState::IDLE;
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