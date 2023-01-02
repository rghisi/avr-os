//
// Created by ghisi on 1/2/23.
//

#ifndef AVR_CLIMATECONTROL_H
#define AVR_CLIMATECONTROL_H

#include "../system/Message.h"

class ClimateControl: public Message {
public:
    ClimateControl(bool enabled, uint8_t temperature, uint8_t humidity);
    ~ClimateControl() override;
    bool enabled;
    uint8_t temperature;
    uint8_t humidity;
};


#endif //AVR_CLIMATECONTROL_H
