//
// Created by ghisi on 19.03.23.
//

#ifndef AVR_STATICPRIORITYQUEUE_H
#define AVR_STATICPRIORITYQUEUE_H

#include "cstdint"
#include "cstdio"
#include "array"

template<typename T, size_t S>
class StaticPriorityQueue {
public:
    bool offer(T element);
    void pop();
    T peek();
    bool isEmpty();
private:
    std::array<T, S> queue;
    uint8_t numberOfElements = 0;
    void pushElementsRightOf(uint8_t index);
    void pullElementsRightOf(uint8_t index);
};

#endif //AVR_STATICPRIORITYQUEUE_H
