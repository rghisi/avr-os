//
// Created by ghisi on 1/3/23.
//

#ifndef AVR_MATH_H
#define AVR_MATH_H


#include "cstdint"

class Math {
public:
    static int8_t max(int8_t a, int8_t b);
    static int8_t min(int8_t a, int8_t b);
    static uint16_t min(uint16_t a, uint16_t b);
    static uint32_t divBy10(uint32_t n);
};


#endif //AVR_MATH_H
