//
// Created by ghisi on 1/10/23.
//

#ifndef AVR_FANCOMMAND_H
#define AVR_FANCOMMAND_H


#include <cstdint>
#include "../../system/Message.h"

class FanCommand: public Message {
public:
    explicit FanCommand(uint8_t power);
    uint8_t power;
    static constexpr uint8_t OFF = 0;
};


#endif //AVR_FANCOMMAND_H
