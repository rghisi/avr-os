//
// Created by ghisi on 11.09.22.
//

#include "Array.h"


template<typename T>
inline void Array<T>::copy(T *source, uint8_t size, T *destination, uint8_t offset) {
    for (uint8_t i = 0; i < size; ++i) {
        destination[i + offset] = source[i];
    }
}

template<typename T>
inline void Array<T>::copy(T *source, uint8_t size, uint8_t offset, T *destination) {
    for (uint8_t i = 0; i < size; ++i) {
        destination[i] = source[i + offset];
    }
}

template<typename T>
inline void Array<T>::copy(T *source, uint8_t size, T *destination) {
    copy(source, size, destination, 0);
}
