//
// Created by ghisi on 12/30/22.
//

#include "TimeTick.h"

TimeTick::TimeTick(uint32_t timestamp): Message(MessageType::TIME_TICK) {
    this->timestamp = timestamp;
}

uint32_t TimeTick::millis() {
    return timestamp;
}
