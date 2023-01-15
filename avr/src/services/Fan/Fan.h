//
// Created by ghisi on 1/10/23.
//

#ifndef AVR_FAN_H
#define AVR_FAN_H


#include "../../system/Subscriber.h"

class Fan: public Subscriber {
public:
    void setup();
    void handle(Message *message) override;

    static void off();

    static void on(uint8_t power);
};


#endif //AVR_FAN_H
