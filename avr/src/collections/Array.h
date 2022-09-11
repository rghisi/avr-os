//
// Created by ghisi on 11.09.22.
//

#ifndef AVR_ARRAY_H
#define AVR_ARRAY_H

#include "cstdint"

template <typename T>
class Array {
public:
    static void copy(T *source, uint8_t size, T *destination);
    static void copy(T *source, uint8_t size, T *destination, uint8_t offset);
    static void copy(T *source, uint8_t size, uint8_t offset, T *destination);
};


#endif //AVR_ARRAY_H
