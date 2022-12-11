/*
 * NetworkInterface.cpp
 *
 *  Created on: Aug 30, 2022
 *      Author: ghisi
 */

#include <avr/io.h>
#include "SerialNetworkInterface.h"
#include "../collections/BlockingQueue.cpp"

SerialNetworkInterface::SerialNetworkInterface(uint8_t networkAddress, USART *usart, EventDispatcher *eventDispatcher) {
    this->address = networkAddress;
    this->usart = usart;
    this->eventDispatcher = eventDispatcher;
    this->packetBuilder = PacketBuilder();
    this->packetReader = PacketReader();
    this->receiveBuffer = BlockingQueue<uint8_t, RECEIVE_BUFFER_SIZE>();
}

inline void SerialNetworkInterface::transmissionFinished() {
    if (!packetReader.hasNextFrame()) {
        usart->disableTransmitter();
    }
}

inline void SerialNetworkInterface::readyToSend() {
    if (packetReader.hasNextFrame()) {
        uint8_t byteToSend = packetReader.nextFrame();
        usart->send(byteToSend);
    } else {
        usart->disableReadyToSendInterrupt();
    }
}

inline void SerialNetworkInterface::frameReceived(uint8_t byte) {
    receiveBuffer.offer(byte);
    auto event = std::make_unique<Event>(Event(EventType::FRAME_RECEIVED, nullptr));
    eventDispatcher->dispatch(std::move(event));
}

EventType SerialNetworkInterface::type() {
    return EventType::PACKET_PRODUCED;
}

bool SerialNetworkInterface::handle(std::unique_ptr<Event> event) {
    switch (event->type()) {
        case PACKET_PRODUCED:
            if (!packetReader.hasNextFrame()) {
                delete packetReader.packet();
                auto *packet = static_cast<Packet*>(event->data());
                packetReader.read(packet);
                usart->enableTransmitterAndReadyToSendInterrupt();
            }
            break;
        case FRAME_RECEIVED:
            processReceivedFrame();
            break;
        default:
            break;
    }
    return true;
}

uint8_t SerialNetworkInterface::getAddress() {
    return address;
}

void SerialNetworkInterface::processReceivedFrame() {
    while (!receiveBuffer.isEmpty()) {
        packetBuilder.add(receiveBuffer.poll());
        if (packetBuilder.isFinished()) {
            auto packet = packetBuilder.build();
            if (packet->isValid()) {
                auto event = std::make_unique<Event>(Event(EventType::PACKET_RECEIVED, packet.release()));
                eventDispatcher->dispatch(std::move(event));
            }
        }
    }
}
