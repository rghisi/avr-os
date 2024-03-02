#include <avr/pgmspace.h>
#include "../avr-libstdcpp/include/bits/functexcept.h"
#include "../avr-libstdcpp/src/list.cc"

#include "comms/Serial.cpp"
#include "impl/SerialPort0.cpp"
#include "system/TaskScheduler.cpp"
#include "cstdio"
#include "cstring"
#include "system/OS.cpp"
#include "console/Shell.cpp"
#include "../generic/AVRContextSwitcher.h"

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
MemoryAllocator<1408> ma = MemoryAllocator<1408>();
MemoryAllocator<1408> *OS::memoryAllocator = &ma;

AVRContextSwitcher cs = AVRContextSwitcher();
ContextSwitcher *OS::contextSwitcher = &cs;

auto serialPort0 = SerialPort0();
auto serial = Serial(&serialPort0);
Serial *Serial::self = &serial;

int main() {
    OS::schedule(new Shell());
    OS::start();

    return 0;
}
