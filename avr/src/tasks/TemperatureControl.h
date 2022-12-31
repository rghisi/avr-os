//
// Created by ghisi on 06.12.22.
//

#ifndef AVR_TEMPERATURECONTROL_H
#define AVR_TEMPERATURECONTROL_H


#include "../system/Task.h"
#include "../dimmer/Dimmer.h"
#include "../pid/PID.h"
#include "../system/EventHandler.h"

class TemperatureControl: public Task, public EventHandler {
public:
    explicit TemperatureControl(Dimmer *dimmer);
    ~TemperatureControl() override = default;
    void run() override;
    uint32_t delay() override;
    Type type() override;

    EventType eventType() override;

    bool handle(Event* event) override;

private:
    int32_t temperatureSetPoint = 3000;
    int32_t currentTemperature = 0;
    int32_t dimmerPosition = 0;
    Dimmer *dimmer;
    PID pid = PID(300, 25, 10);
};


#endif //AVR_TEMPERATURECONTROL_H
