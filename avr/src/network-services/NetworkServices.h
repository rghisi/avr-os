//
// Created by ghisi on 11.09.22.
//

#ifndef AVR_NETWORKSERVICES_H
#define AVR_NETWORKSERVICES_H

#include "../networking/NetworkInterface.h"
#include "../collections/BlockingQueue.h"
#include "Message.h"
#include "Receiver.h"
#include "Sender.h"

class NetworkServices: public Sender {
public:
    NetworkServices(NetworkInterface *networkInterface);
    void processReceiveQueue();
    void processSendQueue();
    void addReceiver(Receiver *receiver);
    bool push(Message *message) override;
    uint8_t getAddress() override;

private:
    NetworkInterface *networkInterface;
    BlockingQueue<Message*> *sendQueue;
    uint8_t address;

    Receiver **receivers;
};


#endif //AVR_NETWORKSERVICES_H
