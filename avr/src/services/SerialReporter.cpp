//
// Created by ghisi on 1/9/23.
//

#include <avr/pgmspace.h>
#include "SerialReporter.h"
#include "cstdio"
#include "../sensors/ClimateReport.h"
#include "../tasks/TemperatureControlStatus.h"
#include "../comms/SerialPacket.h"
#include "cstring"
#include "../tasks/MemoryReport.h"

SerialReporter::SerialReporter(Messaging *messaging) {
    this->messaging = messaging;
}

void SerialReporter::handle(Message *event) {
    switch (event->type()) {
        case CLIMATE_REPORT:
            ClimateReport *climateReport;
            climateReport = static_cast<ClimateReport*>(event);
            temperature = climateReport->temperatureCelsius;
            humidity = climateReport->relativeHumidity >> 10;
            break;
        case TEMPERATURE_CONTROL_STATUS:
            TemperatureControlStatus *temperatureControlStatus;
            temperatureControlStatus = static_cast<TemperatureControlStatus*>(event);
            tcEnabled = temperatureControlStatus->enabled;
            tcPosition = temperatureControlStatus->position;
            break;
        case MEMORY_REPORT:
            MemoryReport *memoryReport;
            memoryReport = static_cast<MemoryReport*>(event);
            freeMemory = memoryReport->freeMemory;
            break;
        default:
            break;
    }
}

void SerialReporter::run() {
    auto stringBuffer = new char[25];
    for (uint8_t i = 0; i < 25; i++) {
        stringBuffer[i] = 0;
    }
    sprintf_P(stringBuffer, PSTR("%u\t%li\t%lu\t%u\t%u\n"), freeMemory, temperature, humidity, tcEnabled, tcPosition);
    messaging->send(new SerialPacket(reinterpret_cast<uint8_t *>(stringBuffer), strlen(stringBuffer)));
}

uint32_t SerialReporter::delay() {
    return 1000;
}

Task::Type SerialReporter::type() {
    return Type::PERIODIC;
}
