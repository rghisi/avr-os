//
// Created by ghisi on 13.10.22.
//

#ifndef AVR_PERIODICPING_H
#define AVR_PERIODICPING_H

#include "../network-services/Ping.h"
#include "../system/Task.h"

class PeriodicPing: public Task {
public:
    explicit PeriodicPing(Ping *ping);
    ~PeriodicPing() override;
    uint32_t delay() override;
    void run() override;
    Type type() override;

private:
    Ping *ping;
};


#endif //AVR_PERIODICPING_H
