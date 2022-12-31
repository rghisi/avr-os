//
// Created by ghisi on 19.10.22.
//

#include "AsyncTaskTest.h"
#include "../system/CpuStats.h"
#include "../system/AsyncChain.h"
#include "../lcd/DisplayTextCommand.h"


AsyncTaskTest::AsyncTaskTest(EventDispatcher *eventDispatcher) {
    this->eventDispatcher = eventDispatcher;
}

uint32_t AsyncTaskTest::delay() {
    return 2000;
}

void AsyncTaskTest::run() {
    auto f1 = [*this]() {
        auto m1 = new char[] {'F', '(', '1', ')', 0x00};
        auto event = new DisplayTextCommand(m1);
        eventDispatcher->dispatch(event);
    };

    auto f2 = [*this]() {
        auto m2 = new char[] {'F', '(', '2', ')', 0x00};
        auto event = new DisplayTextCommand(m2);
        eventDispatcher->dispatch(event);
    };

    auto f3 = [*this]() {
        auto m3 = new char[] {'F', '(', '3', ')', 0x00};
        auto event = new DisplayTextCommand(m3);
        eventDispatcher->dispatch(event);
    };

    auto f4 = [*this]() {
        auto m4 = new char[] {'F', '(', '4', ')', 0x00};
        auto event = new DisplayTextCommand(m4);
        eventDispatcher->dispatch(event);
    };

    auto *asyncChain = new AsyncChain(eventDispatcher);
    asyncChain->then(f1)->wait(250)->then(f2)->wait(250)->then(f3)->wait(250)->then(f4)->schedule();
}

Task::Type AsyncTaskTest::type() {
    return Type::PERIODIC;
}

AsyncTaskTest::~AsyncTaskTest() {
    eventDispatcher = nullptr;
}
