#include <cstdlib>
#include <avr/pgmspace.h>
#include "../avr-libstdcpp/src/functexcept.cc"
#include "../avr-libstdcpp/src/list.cc"
#include <util/delay.h>

#include "hw/avr/ATMega328P.h"
#include "system/TaskScheduler.h"
#include "events/EventLoop.h"
#include "events/Messaging.h"
#include "system/WallClock.h"
#include "comms/Serial.h"
#include "services/InfiniteTask.h"
#include "cstdio"
#include "cstring"
#include "system/OS.h"
#include "std/Random.h"
#include "services/PerformanceReporter.h"
#include "system/MemoryAllocator.h"
#include "services/PiTask.h"
#include "services/AnnoyingTask.h"

void * operator new(size_t size)
{
    return OS::memalloc(size);
}

void operator delete(void * ptr)
{
    OS::memfree(ptr);
}

void * operator new[](size_t size)
{
    return OS::memalloc(size);
}

void operator delete[](void * ptr)
{
    OS::memfree(ptr);
}

void operator delete(void* ptr, unsigned  int x)
{
    OS::memfree(ptr);
}

__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);
extern "C" void __cxa_pure_virtual(void);

int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {};
void __cxa_pure_virtual(void) {};

auto atmega = ATMega328P();
auto wallClock = WallClock();
auto subscriberRegistry = SubscriberRegistry();
//auto eventLoop = EventLoop(&subscriberRegistry, &wallClock);
auto taskScheduler = TaskScheduler(&wallClock);
//auto m = Messaging(&eventLoop);
auto serial = Serial(&atmega);
Serial *Serial::self = &serial;

auto infiniteTaskOne = InfiniteTask(1);
auto infiniteTaskTwo = InfiniteTask(2);
auto infiniteTaskThree = InfiniteTask(3);
auto annoyingTask = AnnoyingTask();
//auto infiniteTaskFour = InfiniteTask(4);
//auto infiniteTaskFive = InfiniteTask(5);
auto piTask = PiTask();
auto performanceReporter = PerformanceReporter();
auto ma = MemoryAllocator<128>();

TaskScheduler *OS::scheduler = &taskScheduler;
//Messaging *OS::messaging = &m;
MemoryAllocator<128> *OS::memoryAllocator = &ma;

int main(void) {
    Random::seed(123);
    atmega.enableTransmitterAndReadyToSendInterrupt();
    atmega.setupTimer0();
    atmega.setTimer0InterruptHandler(&wallClock);
    atmega.enableInterrupts();
//
    subscriberRegistry.subscribe(&serial, SERIAL_SEND);
//
    auto stringBuffer = new char[24];
    sprintf_P(stringBuffer, PSTR("-- Starting --\n\n"));
    Serial::send(stringBuffer, strlen(stringBuffer));
//
//
    taskScheduler.schedule(&infiniteTaskOne);
    taskScheduler.schedule(&infiniteTaskTwo);
    taskScheduler.schedule(&infiniteTaskThree);
//    taskScheduler.schedule(&infiniteTaskFour);
//    taskScheduler.schedule(&infiniteTaskFive);
    taskScheduler.schedule(&piTask);
//    taskScheduler.schedule(&infiniteTaskThree);
    taskScheduler.schedule(&performanceReporter);
    taskScheduler.schedule(&annoyingTask);
    OS::run();

    return 0;
}
