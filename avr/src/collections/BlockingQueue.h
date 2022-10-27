//
// Created by ghisi on 31.08.22.
//

#ifndef AVR_BLOCKINGQUEUE_H
#define AVR_BLOCKINGQUEUE_H
#include <cstdint>
#include "type_traits"

template <typename T, std::size_t S>
class BlockingQueue {
public:
    BlockingQueue();
    bool offer(T item);
    T poll();
    bool isEmpty();
    bool isFull();
    uint8_t itemCount();
    void clear();
private:
    uint8_t capacity;
    uint8_t used;
    uint8_t offerIndex;
    uint8_t pollIndex;
    T queue[S];

};


#endif //AVR_BLOCKINGQUEUE_H
