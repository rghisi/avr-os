//
// Created by ghisi on 13.10.22.
//

#include <util/delay.h>
#include "PeriodicPing.h"

PeriodicPing::PeriodicPing(Ping *ping) {
    this->ping = ping;
}

void PeriodicPing::run() {
    ping->ping(0x0A);
}

uint32_t PeriodicPing::delay() {
    return 500;
}

Task::Type PeriodicPing::type() {
    return Type::PERIODIC;
}

PeriodicPing::~PeriodicPing() {
    ping = nullptr;
}
