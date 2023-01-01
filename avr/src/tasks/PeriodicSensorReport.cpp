//
// Created by ghisi on 10.11.22.
//

#include "PeriodicSensorReport.h"
#include "../sensors/bme280_i2c.h"
#include "memory"
#include "../system/Message.h"
#include "../sensors/BME280Report.h"
#include "../sensors/i2cmaster.h"

PeriodicSensorReport::PeriodicSensorReport(MessageDispatcher *eventDispatcher) {
    this->eventDispatcher = eventDispatcher;
    i2c_init();
    BME280_init();
    BME280_set_filter(BME280_FILTER_16);
    BME280_set_standby(BME280_TSB_10);
    BME280_set_measure(BME280_OVER_16, BME280_HUM);
    BME280_set_measure(BME280_OVER_4,  BME280_PRESS);
    BME280_set_measure(BME280_OVER_16, BME280_TEMP);
    BME280_set_measuremode(BME280_MODE_NORM);
}

void PeriodicSensorReport::run() {
    int32_t temperatureCelsius;
    uint32_t pressureMilliBar;
    uint32_t relativeHumidity;
    BME280_readout(&temperatureCelsius, &pressureMilliBar, &relativeHumidity);
    relativeHumidity = relativeHumidity / 1024;

    auto report = new BME280Report(temperatureCelsius, pressureMilliBar, relativeHumidity);
    eventDispatcher->dispatch(report);
}

uint32_t PeriodicSensorReport::delay() {
    return 1000;
}

Task::Type PeriodicSensorReport::type() {
    return Type::PERIODIC;
}
