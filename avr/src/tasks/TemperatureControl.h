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

    bool handle(std::unique_ptr<Event> event) override;

private:
    int16_t temperatureSetPoint = 300;
    int16_t currentTemperature = 0;
    int16_t dimmerPosition = 0;
    Dimmer *dimmer;
    PID pid = PID(1, 0, 0);
};


#endif //AVR_TEMPERATURECONTROL_H
