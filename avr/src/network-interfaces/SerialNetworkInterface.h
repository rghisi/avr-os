//
// Created by ghisi on 31.08.22.
//

#ifndef AVR_SERIALNETWORKINTERFACE_H
#define AVR_SERIALNETWORKINTERFACE_H
#include "../system/MessageDispatcher.h"
#include "../collections/BlockingQueue.h"
#include "../networking/NetworkInterface.h"
#include "../networking/PacketBuilder.h"
#include "../networking/PacketReader.h"
#include "../hw/USART.h"

class SerialNetworkInterface: public NetworkInterface, public USARTInterruptHandler {
public:
    explicit SerialNetworkInterface(uint8_t networkAddress, USART *usart, EventDispatcher *eventDispatcher);
    ~SerialNetworkInterface() override = default;
    void transmissionFinished() override;
    void readyToSend() override;
    EventType type() override;
    bool handle(std::unique_ptr<Event> event) override;

    void frameReceived(uint8_t byte) override;
    uint8_t getAddress() override;

private:
    void processReceivedFrame();
    uint8_t address;
    PacketBuilder packetBuilder;
    PacketReader packetReader;
    USART *usart;
    EventDispatcher *eventDispatcher;
    static const uint8_t RECEIVE_BUFFER_SIZE = 16;
    BlockingQueue<uint8_t, RECEIVE_BUFFER_SIZE> receiveBuffer;
};

#endif //AVR_SERIALNETWORKINTERFACE_H
