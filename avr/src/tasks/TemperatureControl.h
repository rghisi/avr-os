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
#include "../pid/PID2.h"

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
    static constexpr int32_t Kp = 5120;
    static constexpr int32_t Ki = 128;
    static constexpr int32_t Kd = 10240;
//    PID pid = PID(5120, 128, 10240, 0, Dimmer::MAX_DELAY, 14000, 5000);
    PID2<Kp, Ki, Kd, 0, Dimmer::MAX_DELAY> pid = PID2<Kp, Ki, Kd, 0, Dimmer::MAX_DELAY>();
    bool enabled;
    void handle(ClimateReport *climateReport);
    void handle(TemperatureControlCommand *climateControl);
};


#endif //AVR_TEMPERATURECONTROL_H
