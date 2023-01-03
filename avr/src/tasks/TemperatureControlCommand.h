//
// Created by ghisi on 1/2/23.
//

#ifndef AVR_TEMPERATURECONTROLCOMMAND_H
#define AVR_TEMPERATURECONTROLCOMMAND_H

#include "../system/Message.h"

class TemperatureControlCommand: public Message {
public:
    TemperatureControlCommand(bool enabled, uint8_t temperature, uint8_t humidity);
    ~TemperatureControlCommand() override;
    bool enabled;
    uint8_t temperature;
    uint8_t humidity;
};


#endif //AVR_TEMPERATURECONTROLCOMMAND_H
