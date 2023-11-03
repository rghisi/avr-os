//
// Created by ghisi on 19.03.23.
//

#include "StaticPriorityQueue.h"
#include "algorithm"

template<typename T, size_t S>
bool StaticPriorityQueue<T, S>::offer(T element) {
    if (numberOfElements == queue.max_size()) {
        return false;
    }

    uint8_t insertionIndex;
    T valueAtInsertionIndex = nullptr;
    for (insertionIndex = 0; insertionIndex < S; insertionIndex++) {
        valueAtInsertionIndex = queue[insertionIndex];
        if (valueAtInsertionIndex == nullptr || *element <= *valueAtInsertionIndex) {
            break;
        }
    }

    if (valueAtInsertionIndex != nullptr) {
        pushElementsRightOf(insertionIndex);
    }

    queue[insertionIndex] = element;
    numberOfElements++;

    return true;
}

template<typename T, size_t S>
bool StaticPriorityQueue<T, S>::isEmpty() {
    return numberOfElements == 0;
}

template<typename T, size_t S>
T StaticPriorityQueue<T, S>::peek() {
    if (queue.empty()) {
        return nullptr;
    }

    return queue[0];
}

template<typename T, size_t S>
void StaticPriorityQueue<T, S>::pop() {
    if (numberOfElements > 0) {
        pullElementsRightOf(0);
        numberOfElements--;
    }
}

template<typename T, size_t S>
void StaticPriorityQueue<T, S>::pushElementsRightOf(uint8_t index) {
    for (uint8_t i = (S - 2); i > index; i--) {
        queue[i] = queue[i - 1];
    }
}

template<typename T, size_t S>
void StaticPriorityQueue<T, S>::pullElementsRightOf(uint8_t index) {
    for (uint8_t i = index; i < (S - 1); i++) {
        queue[i] = queue[i+1];
    }
    queue[S - 1] = nullptr;
}