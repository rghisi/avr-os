//
// Created by ghisi on 11.09.22.
//

#ifndef AVR_PACKETRECEIVER_H
#define AVR_PACKETRECEIVER_H

#include "../networking/Packet.h"

class PacketReceiver {
public:
    virtual void receive(Packet *packet) = 0;
    virtual uint8_t service() {
        return 0;
    }
};

#endif //AVR_PACKETRECEIVER_H
