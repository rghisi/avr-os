//
// Created by ghisi on 31.08.22.
//

#ifndef AVR_SERIALNETWORKINTERFACE_H
#define AVR_SERIALNETWORKINTERFACE_H
#include "NetworkInterface.h"
#include "../collections/BlockingQueue.h"
#include "PacketBuilder.h"
#include "../hw/USART.h"

class SerialNetworkInterface: public NetworkInterface, public USARTInterruptHandler {
public:
    explicit SerialNetworkInterface(uint8_t networkAddress, USART *usart);
    ~SerialNetworkInterface() override;
    bool pushToSendQueue(Packet *packet) override;
    bool acceptsPacket() override;
    bool receiveQueueHasPackets() override;
    Packet *popFromReceiveQueue() override;
    void transmissionFinished() override;
    void readyToSend() override;
    void dataReceived(uint8_t receivedByte) override;
    uint8_t getAddress() override;
private:
    bool prepareNextPacket();
    bool isTransmitting;
    uint8_t address;
    Packet* packetBeingSent;
    PacketBuilder* packetBuilder;
    static const uint8_t QUEUE_SIZE = 2;
    BlockingQueue<Packet*> *receiveQueue;
    BlockingQueue<Packet*> *sendQueue;
    BlockingQueue<uint8_t> *sentBytes;
    USART *usart;

    void backoffAndRetry();
};

#endif //AVR_SERIALNETWORKINTERFACE_H
