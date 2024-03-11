//
// Created by ghisi on 11.03.24.
//

#ifndef AVR_AVRCPU_H
#define AVR_AVRCPU_H


#include "../../system/Cpu.h"
#include <avr/interrupt.h>

class AVRCpu: public Cpu {
public:
    void enableInterrupts() override;
    void disableInterrupts() override;
};

void AVRCpu::enableInterrupts() {
    sei();
}

void AVRCpu::disableInterrupts() {

}


#endif //AVR_AVRCPU_H
