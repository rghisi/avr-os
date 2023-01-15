//
// Created by ghisi on 1/10/23.
//

#ifndef AVR_BUZZER_H
#define AVR_BUZZER_H


#include "../../system/Subscriber.h"
#include "../../system/Messaging.h"

class Buzzer: public Subscriber {
public:
    explicit Buzzer(Messaging *messaging);
    void setup();
    void handle(Message *message) override;
    static void on();
    static void off();
private:
    Messaging *messaging;
};


#endif //AVR_BUZZER_H
