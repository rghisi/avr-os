//
// Created by ghisi on 1/9/23.
//

#ifndef AVR_SERIALPACKET_H
#define AVR_SERIALPACKET_H

#include "../events/Message.h"

class SerialPacket: public Message {
public:
    explicit SerialPacket(uint8_t *bytes, uint8_t length);
    ~SerialPacket() override;
    uint8_t *bytes;
    uint8_t length;
};


#endif //AVR_SERIALPACKET_H
