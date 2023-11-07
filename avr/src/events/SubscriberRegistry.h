//
// Created by ghisi on 1/2/23.
//

#ifndef AVR_SUBSCRIBERREGISTRY_H
#define AVR_SUBSCRIBERREGISTRY_H

#include "MessageType.h"
#include "Subscriber.h"

class SubscriberRegistry {
public:
    void subscribe(Subscriber *subscriber, MessageType messageType);

    Subscriber *get(MessageType type);

private:
    std::array<Subscriber*, MessageType::MAX> subscribers;
    uint16_t multiplexerBitmap = 0;
    void setMultiplexed(MessageType type);
    [[nodiscard]] bool isMultiplexed(MessageType type) const;
};


#endif //AVR_SUBSCRIBERREGISTRY_H
