//
// Created by ghisi on 19.10.22.
//

#include "functional"
#include "memory"
#include "AsyncTaskTest.h"
#include "../system/CpuStats.h"
#include "../system/AsyncChain.h"


AsyncTaskTest::AsyncTaskTest(EventDispatcher *eventDispatcher) {
    this->eventDispatcher = eventDispatcher;
    m1 = new char[] {'F', '(', '1', ')', 0x00};
    m2 = new char[] {'F', '(', '2', ')', 0x00};
    m3 = new char[] {'F', '(', '3', ')', 0x00};
    m4 = new char[] {'F', '(', '4', ')', 0x00};
}

uint32_t AsyncTaskTest::delay() {
    return 2000;
}

void AsyncTaskTest::run() {
    auto f1 = [*this]() {
        eventDispatcher->dispatch(new Event(EventType::SHOW_TEXT_REQUESTED, m1));
    };

    auto f2 = [*this]() {
        eventDispatcher->dispatch(new Event(EventType::SHOW_TEXT_REQUESTED, m2));
    };

    auto f3 = [*this]() {
        eventDispatcher->dispatch(new Event(EventType::SHOW_TEXT_REQUESTED, m3));
    };

    auto f4 = [*this]() {
        eventDispatcher->dispatch(new Event(EventType::SHOW_TEXT_REQUESTED, m4));
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
