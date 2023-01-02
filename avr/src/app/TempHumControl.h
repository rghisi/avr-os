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
    TempHumControl();
    ~TempHumControl() override = default;
    void run() override;
    uint32_t delay() override;
    Type type() override;
    bool handle(Message* event) override;

private:
    uint32_t temperature;
    uint32_t humidity;
    int16_t setTemperature;
    int16_t temperatureOutput;
    int16_t setHumidity;
    int16_t humidityOutput;
    PID temperaturePid = PID(0, 0, 0);
    PID humidityPid = PID(0, 0, 0);
    static constexpr MessageType messageTypes[1] = {CLIMATE_REPORT};
    static constexpr uint8_t messageTypeCount = 1;
};


#endif //AVR_TEMPHUMCONTROL_H
