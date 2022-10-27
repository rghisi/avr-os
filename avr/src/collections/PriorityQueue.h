//
// Created by ghisi on 26.10.22.
//

#ifndef AVR_PRIORITYQUEUE_H
#define AVR_PRIORITYQUEUE_H

#include <cstdint>
#include "memory"

template <typename E>
struct Element {
    E element;
    Element<E> *next;
    ~Element();
};

template<typename E>
Element<E>::~Element() = default;

template <typename T>
class PriorityQueue {
public:
    PriorityQueue();
    bool offer(T element);
    void pop();
    T peek();
    bool isEmpty();
private:
    Element<T> *first;
};


#endif //AVR_PRIORITYQUEUE_H
