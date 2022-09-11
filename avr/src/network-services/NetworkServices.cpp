//
// Created by ghisi on 11.09.22.
//

#include "NetworkServices.h"
#include "../collections/Array.cpp"
#include "../collections/BlockingQueue.cpp"

#include <avr/io.h>
#include <avr/delay.h>

NetworkServices::NetworkServices(NetworkInterface *networkInterface) {
    this->networkInterface = networkInterface;
    this->address = networkInterface->getAddress();
    this->sendQueue = new BlockingQueue<Message*>(2);
    this->receivers = new Receiver*[16];
}

void NetworkServices::addReceiver(Receiver *receiver) {
    receivers[receiver->getPort()] = receiver;
}

void NetworkServices::processReceiveQueue() {
    while (networkInterface->receiveQueueHasPackets()) {
        auto *packet = networkInterface->popFromReceiveQueue();
        auto *data = new uint8_t[packet->payloadSize];
        Array<uint8_t>::copy(packet->packetData, packet->payloadSize, Packet::HEADER_SIZE, data);
        auto *message = new Message(packet->destination, packet->source, data, packet->payloadSize);
//        auto *receiver = receivers[message->port];
//        if (receiver->getPort() == 0x01) {
//            PORTB = 0x00;
//            _delay_ms(500);
//            PORTB = 0xFF;
//            _delay_ms(500);
//            PORTB = 0x00;
//            _delay_ms(500);
//            PORTB = 0xFF;
//            _delay_ms(500);
//        }
//        receiver->receive(message);
        delete packet;
        delete[] data;
    }
}

void NetworkServices::processSendQueue() {
    PORTB = 0x00;
    _delay_ms(150);
    PORTB = 0xFF;
    _delay_ms(200);
    while (!sendQueue->isEmpty()) { // && networkInterface->acceptsPacket()) {
        PORTB = 0x00;
        _delay_ms(150);
        PORTB = 0xFF;
        _delay_ms(300);
        auto *message = sendQueue->poll();

        PORTB = 0x00;
        _delay_ms(150);
        PORTB = 0xFF;
        _delay_ms(300);
        auto *packet = new Packet(message->destination, message->source, 0x00, 0x01, 0x00, message->serialized, message->size);

        PORTB = 0x00;
        _delay_ms(150);
        PORTB = 0xFF;
        _delay_ms(300);
        networkInterface->pushToSendQueue(packet);

        PORTB = 0x00;
        _delay_ms(150);
        PORTB = 0xFF;
        _delay_ms(300);
        delete message;

        PORTB = 0x00;
        _delay_ms(150);
        PORTB = 0xFF;
        _delay_ms(300);
    }
}

bool NetworkServices::push(Message *message) {
    return sendQueue->offer(message);
}

uint8_t NetworkServices::getAddress() {
    return address;
}
