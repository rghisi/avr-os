//
// Created by ghisi on 11.03.24.
//

#ifndef AVR_CPU_H
#define AVR_CPU_H


class Cpu {
public:
    virtual void enableInterrupts() = 0;
    virtual void disableInterrupts() = 0;
};


#endif //AVR_CPU_H
