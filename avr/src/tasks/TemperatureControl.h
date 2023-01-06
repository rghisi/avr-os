//
// Created by ghisi on 06.12.22.
//

#ifndef AVR_TEMPERATURECONTROL_H
#define AVR_TEMPERATURECONTROL_H


#include "../system/Task.h"
#include "../dimmer/Dimmer.h"
#include "../pid/PID.h"
#include "../system/Subscriber.h"
#include "../sensors/ClimateReport.h"
#include "TemperatureControlCommand.h"
#include "../system/Messaging.h"

class TemperatureControl: public Task, public Subscriber {
public:
    explicit TemperatureControl(Messaging *messaging, Dimmer *dimmer);
    ~TemperatureControl() override = default;
    void run() override;
    uint32_t delay() override;
    Type type() override;
    void handle(Message *event) override;
private:
    int32_t temperatureSetPoint = 0;
    int32_t currentTemperature = 0;
    Messaging *messaging;
    Dimmer *dimmer;
    PID pid = PID(300, 25, 10, 0, 16000, 140, 200);
    bool enabled;
    void handle(ClimateReport *climateReport);
    void handle(TemperatureControlCommand *climateControl);
};


#endif //AVR_TEMPERATURECONTROL_H
