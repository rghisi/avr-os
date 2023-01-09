//
// Created by ghisi on 1/3/23.
//

#ifndef AVR_TEMPERATURECONTROLSTATUS_H
#define AVR_TEMPERATURECONTROLSTATUS_H


#include "../system/Message.h"

class TemperatureControlStatus: public Message {
public:
    TemperatureControlStatus(bool enabled, uint16_t position);
    ~TemperatureControlStatus() override;
    bool enabled;
    uint16_t position;
};


#endif //AVR_TEMPERATURECONTROLSTATUS_H
