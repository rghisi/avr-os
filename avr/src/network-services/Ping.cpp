//
// Created by ghisi on 11.09.22.
//

#include "Ping.h"
#include "../collections/Array.cpp"

Ping::Ping(EventDispatcher *eventDispatcher) {
    this->eventDispatcher = eventDispatcher;
}

void Ping::ping(uint8_t destination) {
    auto *pingBytes = Array<uint8_t>::copy(pingMessage, 0x04);
    auto *ping = new Packet(destination, 0xAA, 0x00, Ping::SERVICE, pingBytes, 0x04);
    auto *event = new Event(EventType::PACKET_DISPATCHED, ping);
    eventDispatcher->dispatch(event);
}

void Ping::pong(uint8_t destination) {
    auto *pongBytes = Array<uint8_t>::copy(pongMessage, 0x04);
    auto *pong = new Packet(destination, 0xAA, 0x00, Ping::SERVICE, pongBytes, 0x04);
    auto *event = new Event(EventType::PACKET_DISPATCHED, pong);
    eventDispatcher->dispatch(event);
}

bool Ping::isPing(Packet *packet) {
    return packet->service() == SERVICE &&
           packet->payloadLength() == 0x04 &&
           packet->payload()[0] == pingMessage[0] &&
           packet->payload()[1] == pingMessage[1] &&
           packet->payload()[2] == pingMessage[2] &&
           packet->payload()[3] == pingMessage[3];
}

bool Ping::handle(Event *event) {
    auto *packet = static_cast<Packet *>(event->data());
    if (isPing(packet)) {
        pong(packet->source());
    }
    delete packet;
    return true;
}

EventType Ping::type() {
    return PING_RECEIVED;
}
