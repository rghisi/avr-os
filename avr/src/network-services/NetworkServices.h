//
// Created by ghisi on 11.09.22.
//

#ifndef AVR_NETWORKSERVICES_H
#define AVR_NETWORKSERVICES_H

#include "../networking/NetworkInterface.h"
#include "../collections/BlockingQueue.h"
#include "PacketReceiver.h"
#include "PacketSender.h"
#include "../networking/PacketBuilder.h"
#include "../system/EventLoop.h"
#include "../system/MessageDispatcher.h"

class NetworkServices: public EventHandler {
public:
    explicit NetworkServices(EventDispatcher *eventDispatcher);
    EventType type() override;
    bool handle(std::unique_ptr<Event> event) override;

private:
    NetworkInterface *networkInterface;
    BlockingQueue<Packet*, 4> receiveBuffer;
    BlockingQueue<Packet*, 4> sendBuffer;
    uint8_t address;
    PacketReceiver *receivers[16]{};
    EventDispatcher *eventDispatcher;
};


#endif //AVR_NETWORKSERVICES_H
