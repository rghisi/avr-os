#include <cstdlib>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "../avr-libstdcpp/src/functexcept.cc"
#include "../avr-libstdcpp/src/list.cc"

#include "hw/avr/ATMega328P.h"
#include "system/TaskScheduler.h"
#include "system/EventLoop.h"
#include "system/Messaging.h"
#include "system/WallClock.h"
#include "comms/Serial.h"
#include "services/InfiniteTask.h"
#include "comms/SerialPacket.h"
#include "cstdio"
#include "cstring"
#include "system/OS.h"
#include "std/Random.h"
#include "services/PerformanceReporter.h"
#include "system/MemoryAllocator.h"
#include "services/PiTask.h"

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
auto eventLoop = EventLoop(&subscriberRegistry, &wallClock);
auto taskScheduler = TaskScheduler(&wallClock, &eventLoop);
auto m = Messaging(&eventLoop);
auto serial = Serial(&atmega);
auto infiniteTaskOne = InfiniteTask(1);
auto infiniteTaskTwo = InfiniteTask(2);
//auto infiniteTaskThree = InfiniteTask(3);
//auto infiniteTaskFour = InfiniteTask(4);
//auto infiniteTaskFive = InfiniteTask(5);
//auto piTask = PiTask();
auto performanceReporter = PerformanceReporter();
auto ma = MemoryAllocator<256>();

TaskScheduler *OS::scheduler = &taskScheduler;
Messaging *OS::messaging = &m;
MemoryAllocator<256> *OS::memoryAllocator = &ma;

//[[maybe_unused]] extern int __heap_start, __heap_end, *__brkval;

int main(void) {
    Random::seed(123);
//    auto a = (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
    atmega.setInterruptHandler(&serial);
    atmega.enableTransmitterAndReadyToSendInterrupt();
    atmega.setupTimer0();
    atmega.setTimer0InterruptHandler(&wallClock);
    auto a = new uint8_t[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto b = new uint8_t[7]{11, 12, 13, 14, 15, 16, 17};
//    atmega.setupTimer1();
    atmega.setupExternalInterrupt();
    atmega.enableInterrupts();
//
    subscriberRegistry.subscribe(&serial, SERIAL_SEND);
//
    auto stringBuffer = new char[24];
    sprintf_P(stringBuffer, PSTR("-- Starting --\n\n"));
    auto *event = new SerialPacket(reinterpret_cast<uint8_t *>(stringBuffer), strlen(stringBuffer));
    OS::send(event);
//
//
    taskScheduler.schedule(&infiniteTaskOne);
    taskScheduler.schedule(&infiniteTaskTwo);
//    taskScheduler.schedule(&infiniteTaskThree);
//    taskScheduler.schedule(&infiniteTaskFour);
//    taskScheduler.schedule(&piTask);
//    taskScheduler.schedule(&infiniteTaskThree);
    taskScheduler.schedule(&performanceReporter);
    OS::run();

    return 0;
}
