//
// Created by ghisi on 10.09.22.
//

#ifndef AVR_RANDOM_H
#define AVR_RANDOM_H

#include <stdint.h>

class Random {
public:
    static uint8_t next();
    static void seed(uint8_t);
private:
    static uint8_t last;
    static uint8_t offset;
    static const uint8_t sequence[];
};


#endif //AVR_RANDOM_H
