#include <avr/pgmspace.h>
#include "../avr-libstdcpp/src/functexcept.cc"
#include "../avr-libstdcpp/src/list.cc"

#include "hw/avr/ATMega328P.h"
#include "system/TaskScheduler.h"
#include "events/EventLoop.h"
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
#include "services/Console.h"
#include "hw/avr/AVRContextSwitcher.h"

extern "C" {
    void *malloc(size_t size) {
        return OS::memalloc(size);
    }

    void free(void *ptr) {
        OS::memfree(ptr);
    }
}
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

TaskScheduler ta = TaskScheduler();
TaskScheduler *OS::scheduler = &ta;
MemoryAllocator<1152> ma = MemoryAllocator<1152>();
MemoryAllocator<1152> *OS::memoryAllocator = &ma;

AVRContextSwitcher cs = AVRContextSwitcher();
ContextSwitcher *OS::contextSwitcher = &cs;

auto atmega = ATMega328P();
auto serial = Serial(&atmega);
Serial *Serial::self = &serial;

auto performanceReporter = PerformanceReporter();

int main() {
    atmega.enableTransmitter();

    OS::schedule(&performanceReporter);
    OS::schedule(new Console());
    OS::start();

    return 0;
}
