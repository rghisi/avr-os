//
// Created by ghisi on 19.10.22.
//

#ifndef AVR_ASYNCTASKTEST_H
#define AVR_ASYNCTASKTEST_H


#include "../system/Task.h"
#include "../system/EventHandler.h"
#include "../system/EventDispatcher.h"

class AsyncTaskTest : public Task {
public:
    explicit AsyncTaskTest(EventDispatcher *eventDispatcher);
    ~AsyncTaskTest() override;
    uint32_t delay() override;
    void run() override;
    Type type() override;

private:
    char *m1;
    char *m2;
    char *m3;
    char *m4;
    EventDispatcher *eventDispatcher;
};


#endif //AVR_ASYNCTASKTEST_H
