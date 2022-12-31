//
// Created by ghisi on 12/30/22.
//

#include "TimeTickData.h"

TimeTickData::TimeTickData(uint32_t timestamp) {
    this->timestamp = timestamp;
}

uint32_t TimeTickData::millis() {
    return timestamp;
}
