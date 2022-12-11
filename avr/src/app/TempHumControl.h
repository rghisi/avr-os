//
// Created by ghisi on 14.11.22.
//

#ifndef AVR_TEMPHUMCONTROL_H
#define AVR_TEMPHUMCONTROL_H


#include "../pid/PID.h"
#include "../system/Task.h"
#include "../system/EventHandler.h"

class TempHumControl: public Task, public EventHandler {
public:
    ~TempHumControl() override = default;
    void run() override;
    uint32_t delay() override;
    Type type() override;

    bool handle(std::unique_ptr<Event> event) override;

    EventType eventType() override;

private:
    uint32_t temperature;
    uint32_t humidity;
    int16_t setTemperature;
    int16_t temperatureOutput;
    int16_t setHumidity;
    int16_t humidityOutput;
    PID temperaturePid;
    PID humidityPid;
};


#endif //AVR_TEMPHUMCONTROL_H
