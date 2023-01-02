//
// Created by ghisi on 1/2/23.
//

#include "SubscriberRegistry.h"
#include "HandlerMultiplexer.h"

void SubscriberRegistry::subscribe(Subscriber *subscriber, MessageType messageType) {
    auto registered = subscribers[messageType];
    if (registered == nullptr) {
        subscribers[messageType] = subscriber;
    } else {
        if (isMultiplexed(messageType)) {
            auto multiplexer = static_cast<HandlerMultiplexer*>(registered);
            multiplexer->add(subscriber);
        } else {
            auto multiplexer = new HandlerMultiplexer();
            multiplexer->add(registered);
            multiplexer->add(subscriber);
            subscribers[messageType] = multiplexer;
            setMultiplexed(messageType);
        }
    }
}

void SubscriberRegistry::setMultiplexed(MessageType type) {
    multiplexerBitmap |= 0x01 << (uint8_t)type;
}

bool SubscriberRegistry::isMultiplexed(MessageType type) const {
    return 0x01 & (multiplexerBitmap >> (uint8_t)type);
}

Subscriber *SubscriberRegistry::get(MessageType type) {
    return subscribers[type];
}
