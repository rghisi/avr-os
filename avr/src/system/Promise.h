//
// Created by ghisi on 05.11.23.
//

#ifndef AVR_PROMISE_H
#define AVR_PROMISE_H

class Promise {
public:
    Promise() = default;
    explicit Promise(void *value) {
        this->value = value;
    }

    ~Promise() {

    }

    [[nodiscard]] bool isCompleted() const {
        return completed;
    }
    void complete() {
        completed = true;
    }
    void *value = nullptr;
private:
    bool completed = false;
};
#endif //AVR_PROMISE_H
