//
// Created by ghisi on 1/9/23.
//

#ifndef AVR_SERIALREPORTER_H
#define AVR_SERIALREPORTER_H


#include "../system/Task.h"
#include "../hw/USART.h"
#include "../system/Subscriber.h"
#include "../system/Messaging.h"

class SerialReporter: public Task, public Subscriber {
public:
    explicit SerialReporter(Messaging *messaging);
    ~SerialReporter() override = default;
    void run() override;
    uint32_t delay() override;
    Type type() override;

    void handle(Message *event) override;

private:
    Messaging *messaging;
    int32_t temperature = 0;
    uint32_t humidity = 0;
    bool tcEnabled = false;
    uint16_t tcPosition = 0;
    uint16_t freeMemory = 0;
};


#endif //AVR_SERIALREPORTER_H
