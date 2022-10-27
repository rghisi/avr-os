//
// Created by ghisi on 11.09.22.
//

#ifndef AVR_PACKETSENDER_H
#define AVR_PACKETSENDER_H

class PacketSender {
public:
    virtual bool send(Packet *packet) = 0;
    virtual uint8_t sourceAddress() = 0;
};

#endif //AVR_PACKETSENDER_H
