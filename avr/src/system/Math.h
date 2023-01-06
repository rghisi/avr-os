//
// Created by ghisi on 1/3/23.
//

#ifndef AVR_MATH_H
#define AVR_MATH_H

#include "cstdint"

class Math {
public:
    template<typename T>
    static T min(T a, T b) {
            return a < b ? a : b;
    }

    template<typename T>
    static T max(T a, T b) {
        return a > b ? a : b;
    }

    static uint32_t divBy10(uint32_t n);
};


#endif //AVR_MATH_H
