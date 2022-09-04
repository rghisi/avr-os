//
// Created by ghisi on 04.09.22.
//

#ifndef AVR_CRC_H
#define AVR_CRC_H

#include <stdint.h>

class CRC {
public:
    static uint8_t calculate(const uint8_t* message, uint8_t nBytes);
    static uint8_t table[256];
};


#endif //AVR_CRC_H
