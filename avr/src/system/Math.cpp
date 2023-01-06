//
// Created by ghisi on 1/3/23.
//

#include "Math.h"

uint32_t Math::divBy10(uint32_t n) {
    uint32_t q, r;
    q = (n >> 1) + (n >> 2);
    q = q + (q >> 4);
    q = q + (q >> 8);
    q = q + (q >> 16);
    q = q >> 3;
    r = n - (((q << 2) + q) << 1);
    return q + (r > 9);
}