//
// Created by ghisi on 19.10.22.
//

#ifndef AVR_ASYNCTASKTEST_H
#define AVR_ASYNCTASKTEST_H


#include "../system/Task.h"
#include "../system/Subscriber.h"
#include "../system/Messaging.h"

class AsyncTaskTest : public Task {
public:
    explicit AsyncTaskTest(Messaging *eventDispatcher);
    ~AsyncTaskTest() override;
    uint32_t delay() override;
    void run() override;
    Type type() override;

private:
    Messaging *eventDispatcher;
};


#endif //AVR_ASYNCTASKTEST_H
