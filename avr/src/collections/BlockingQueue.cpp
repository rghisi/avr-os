//
// Created by ghisi on 31.08.22.
//
#include "BlockingQueue.h"

template <typename T>
BlockingQueue<T>::BlockingQueue(uint8_t size) {
    this->queue = new T[size];
    this->offerIndex = 0;
    this->pollIndex = 0;
    this->used = 0;
    this->capacity = size;
}

template <typename T>
BlockingQueue<T>::~BlockingQueue() {
    delete[] this->queue;
}

template <typename T>
bool BlockingQueue<T>::isEmpty() {
    return used == 0;
}

template <typename T>
bool BlockingQueue<T>::isFull() {
    return used == capacity;
}

template<typename T>
bool BlockingQueue<T>::offer(T item) {
    if (used < capacity) {
        queue[offerIndex] = item;
        offerIndex++;
        used++;
        if (offerIndex == capacity) {
            offerIndex = 0;
        }

        return true;
    }

    return false;
}

template<typename T>
T BlockingQueue<T>::poll() {
    if (used > 0) {
        T item = this->queue[pollIndex];
        if constexpr (std::is_integral<T>::value) {
            this->queue[pollIndex] = 0;
        } else {
            this->queue[pollIndex] = nullptr;

        }
        used--;
        pollIndex++;
        if (pollIndex == capacity) {
            pollIndex = 0;
        }
        return item;
    }

    if constexpr (std::is_pointer<T>::value) {
        return nullptr;
    } else {
        return 0;
    }
}

template<typename T>
void BlockingQueue<T>::clear() {
    this->offerIndex = 0;
    this->pollIndex = 0;
    this->used = 0;
}


//0  1   2   3
//o  p         full
//op           start=>empty