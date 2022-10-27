//
// Created by ghisi on 26.10.22.
//

#include "PriorityQueue.h"

template<typename T>
PriorityQueue<T>::PriorityQueue() {
    first = new Element<T>{ .element = nullptr, .next = nullptr};
}

template<typename T>
bool PriorityQueue<T>::offer(T element) {
    auto *current = first;
    while (current->element != nullptr && (*element) > (*current->element)) {
        current = current->next;
    }

    auto *next = new Element<T>{ .element = current->element, .next = current->next};
    current->element = element;
    current->next = next;

    return true;
}

template<typename T>
void PriorityQueue<T>::pop() {
    if (first->element != nullptr) {
        auto *firstElement = first;
        first = first->next;
        firstElement->element = nullptr;
        firstElement->next = nullptr;
        delete firstElement;
    }
}

template<typename T>
bool PriorityQueue<T>::isEmpty() {
    return first->element == nullptr;
}

template<typename T>
T PriorityQueue<T>::peek() {
    return first->element;
}
