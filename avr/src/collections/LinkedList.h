//
// Created by ghisi on 11.03.24.
//

#ifndef AVR_LINKEDLIST_H
#define AVR_LINKEDLIST_H

template <typename T>
class LinkedList {
public:
    void push(T t);
    T pop();
    bool isEmpty();
private:
    template <typename V>
    class Node {
    public:
        explicit Node(V v) {
            value = v;
            next = nullptr;
        }
        V value;
        Node* next;
    };

    Node<T>* first = nullptr;
    Node<T>* last = nullptr;
};

template<typename T>
bool LinkedList<T>::isEmpty() {
    return first == nullptr;
}

template<typename T>
void LinkedList<T>::push(T t) {
    auto node = new Node<T>(t);
    if (first == nullptr) {
        first = node;
        last = first;
    } else {
        last->next = node;
        last = node;
    }
}

template<typename T>
T LinkedList<T>::pop() {
    auto value = first->value;
    if (first == last) {
        delete first;
        first = nullptr;
        last = nullptr;
    } else {
        auto popped = first;
        first = first->next;
        delete popped;
    }

    return value;
}


#endif //AVR_LINKEDLIST_H
