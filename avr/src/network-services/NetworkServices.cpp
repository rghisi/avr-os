//
// Created by ghisi on 11.09.22.
//

#include "NetworkServices.h"
#include "../collections/Array.cpp"
#include "../collections/BlockingQueue.cpp"
#include "Services.h"

NetworkServices::NetworkServices(EventDispatcher *eventDispatcher) {
    this->eventDispatcher = eventDispatcher;
}

EventType NetworkServices::type() {
    return PACKET_RECEIVED;
}

bool NetworkServices::handle(std::unique_ptr<Event> event) {
    auto *packet = static_cast<Packet*>(event->data());
    if (packet->service() == Services::PING) {
            auto newEvent = std::make_unique<Event>(Event(EventType::PING_RECEIVED, packet));
            eventDispatcher->dispatch(std::move(newEvent));
    } else {
        delete packet;
    }

    return true;
}
