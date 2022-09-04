//
// Created by ghisi on 31.08.22.
//

#ifndef AVR_BLOCKINGQUEUE_H
#define AVR_BLOCKINGQUEUE_H
#include <stdint.h>

template <typename T>
class BlockingQueue {
public:
    BlockingQueue(uint8_t size);
    ~BlockingQueue();
    bool offer(T* item);
    T* poll();
    bool isEmpty();
    bool isFull();
private:
    uint8_t capacity;
    uint8_t used;
    uint8_t offerIndex;
    uint8_t pollIndex;
    T** queue;
};


#endif //AVR_BLOCKINGQUEUE_H
