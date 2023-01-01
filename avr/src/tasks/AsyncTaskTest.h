//
// Created by ghisi on 19.10.22.
//

#ifndef AVR_ASYNCTASKTEST_H
#define AVR_ASYNCTASKTEST_H


#include "../system/Task.h"
#include "../system/EventHandler.h"
#include "../system/MessageDispatcher.h"

class AsyncTaskTest : public Task {
public:
    explicit AsyncTaskTest(MessageDispatcher *eventDispatcher);
    ~AsyncTaskTest() override;
    uint32_t delay() override;
    void run() override;
    Type type() override;

private:
    MessageDispatcher *eventDispatcher;
};


#endif //AVR_ASYNCTASKTEST_H
