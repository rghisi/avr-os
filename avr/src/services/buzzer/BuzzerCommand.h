//
// Created by ghisi on 1/10/23.
//

#ifndef AVR_BUZZERCOMMAND_H
#define AVR_BUZZERCOMMAND_H


#include "../../system/Message.h"

class BuzzerCommand: public Message {
public:
    explicit BuzzerCommand(uint8_t duration);
    ~BuzzerCommand() override;
    uint8_t duration;
};


#endif //AVR_BUZZERCOMMAND_H
