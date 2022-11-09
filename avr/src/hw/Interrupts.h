//
// Created by ghisi on 09.11.22.
//

#ifndef AVR_INTERRUPTS_H
#define AVR_INTERRUPTS_H

class Interrupts {
public:
    virtual void enableInterrupts() = 0;
    virtual void disableInterrupts() = 0;
};

#endif //AVR_INTERRUPTS_H
