//
// Created by ghisi on 31.08.22.
//
#include "BlockingQueue.h"

template <typename T, std::size_t S>
BlockingQueue<T, S>::BlockingQueue() {
    offerIndex = 0;
    pollIndex = 0;
    used = 0;
    capacity = S;
}

template <typename T, std::size_t S>
bool BlockingQueue<T, S>::isEmpty() {
    return used == 0;
}

template <typename T, std::size_t S>
bool BlockingQueue<T, S>::isFull() {
    return used == capacity;
}

template<typename T, std::size_t S>
bool BlockingQueue<T, S>::offer(T item) {
    if (used < capacity) {
        used++;
        queue[offerIndex] = item;
        offerIndex++;
        if (offerIndex == capacity) {
            offerIndex = 0;
        }

        return true;
    }

    return false;
}

template<typename T, std::size_t S>
T BlockingQueue<T, S>::poll() {
    if (used > 0) {
        used--;
        T item = this->queue[pollIndex];
        if constexpr (std::is_integral<T>::value) {
            this->queue[pollIndex] = 0;
        } else {
            this->queue[pollIndex] = nullptr;
        }
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

template<typename T, std::size_t S>
void BlockingQueue<T, S>::clear() {
    this->offerIndex = 0;
    this->pollIndex = 0;
    this->used = 0;
}

template<typename T, std::size_t S>
uint8_t BlockingQueue<T, S>::itemCount() {
    return used;
}
