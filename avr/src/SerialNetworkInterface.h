//
// Created by ghisi on 31.08.22.
//

#ifndef AVR_SERIALNETWORKINTERFACE_H
#define AVR_SERIALNETWORKINTERFACE_H
#include "NetworkInterface.h"
#include "BlockingQueue.h"
#include "PacketBuilder.h"

class SerialNetworkInterface: public NetworkInterface {
public:
    explicit SerialNetworkInterface(uint8_t networkAddress);
    ~SerialNetworkInterface() override;
    bool pushToSendQueue(Packet* packet) override;
    bool acceptsPacket() override;
    bool receiveQueueHasPackets() override;
    Packet* popFromReceiveQueue() override;
    uint8_t nextByteToSend() override;
    void handleReadyToSendInterrupt();
    void handleDataReceivedInterrupt();
    void handleTransmissionFinished();
private:
    void preparePacketToSend();
    void toggleTransmitter();
    void toggleReceiver();
    enum class DataState { WAITING_DATA, DATA_READY };
    enum class IOState { IDLE, RUNNING, FINALIZING };
    DataState txDataState;
    DataState rxDataState;
    IOState txState;
    IOState rxState;
    uint8_t address;
    Packet* packetBeingSent;
    PacketBuilder* packetBuilder;
    static const uint8_t QUEUE_SIZE = 2;
    BlockingQueue<Packet>* receiveQueue;
    BlockingQueue<Packet>* sendQueue;
};

#endif //AVR_SERIALNETWORKINTERFACE_H
