#include <avr/io.h>
#include <util/delay.h>
#include <cstdlib>
#include "../avr-libstdcpp/src/functexcept.cc"
#include "../avr-libstdcpp/src/list.cc"
#include <avr/wdt.h>

#include "hw/avr/ATMega328P.h"
#include "system/TaskScheduler.h"
#include "system/EventLoop.h"
#include "system/EventDispatcher.h"
#include "system/WallClock.h"
#include "lcd/Display.h"
#include "tasks/AsyncTaskTest.h"
#include "system/AsyncExecutor.h"
#include "tasks/PeriodicMemoryReport.h"
#include "input/KeyPad.h"
#include "tasks/PeriodicSensorReport.h"
#include "dimmer/Dimmer.h"
#include "tasks/TemperatureControl.h"
#include "input/Dial.h"
#include "app/Test.h"

void * operator new(size_t size)
{
    return malloc(size);
}

void operator delete(void * ptr)
{
    free(ptr);
}

void * operator new[](size_t size)
{
    return malloc(size);
}

void operator delete[](void * ptr)
{
    free(ptr);
}

void operator delete(void* ptr, unsigned  int x)
{
    free(ptr);
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
auto display = Display();
auto wallClock = WallClock();
auto taskScheduler = TaskScheduler(&wallClock);
auto eventLoop = EventLoop();
auto eventDispatcher = EventDispatcher(&eventLoop);
auto asyncExecutor = AsyncExecutor(&taskScheduler, &eventDispatcher);
auto periodicMemoryReport = PeriodicMemoryReport(&wallClock, &eventDispatcher);
auto keyPad = KeyPad(&eventDispatcher);
auto dial = Dial(&eventDispatcher);
auto periodicSensorReport = PeriodicSensorReport(&eventDispatcher);
auto dimmer = Dimmer(&atmega, &atmega);
//auto temperatureControl = TemperatureControl(&dimmer);
auto test = Test(&eventDispatcher, &dimmer);

int main(void) {
//    uint8_t statusLed = _BV(PORTB5);
//    DDRB |= statusLed;
//    PORTB &= ~statusLed;
//    _delay_ms(1000);
//    PORTB |= statusLed;
//    _delay_ms(1000);
//    PORTB &= ~statusLed;

//    DDRC |= _BV(PORTC0);


    atmega.setupTimer0();
    atmega.setTimer0InterruptHandler(&wallClock);
    atmega.setupTimer1();
    atmega.setTimer1CompareMatchAInterruptHandler(&dimmer);
    atmega.setupExternalInterrupt();
    atmega.setExternalInterruptHandler(&dimmer);
    atmega.enableInterrupts();

    keyPad.setup();
    dial.setup();

    eventLoop.addHandler(&asyncExecutor);
    eventLoop.addHandler(&asyncExecutor, ASYNC_CHAIN_SCHEDULED);
    eventLoop.addHandler(&display);
    eventLoop.addHandler(&display, SHOW_TEXT_REQUESTED);
    eventLoop.addHandler(&display, MEMORY_STATS_READ);
    eventLoop.addHandler(&display, SENSOR_READ);
    eventLoop.addHandler(&display, USER_INPUT);
//    eventLoop.addHandler(&temperatureControl);
    //eventLoop.addHandler(&test);

    taskScheduler.schedule(&periodicMemoryReport);
    taskScheduler.schedule(&keyPad);
    taskScheduler.schedule(&dial);
    taskScheduler.schedule(&periodicSensorReport);
//    taskScheduler.schedule(&temperatureControl);

//    auto *dimmerCalibrationTask = new AsyncChain(&eventDispatcher);
//    dimmerCalibrationTask
//            ->wait(1000)
//            ->then([]() {dimmer.enable();})
//            ->wait(500)
//            ->then([]() {dimmer.setPosition(64);})
//            ->wait(2000)
//            ->then([]() {dimmer.setPosition(128);})
//            ->wait(2000)
//            ->then([]() {dimmer.setPosition(255);})
//            ->wait(2000)
//            ->then([]() {dimmer.setPosition(16);})
//            ->wait(2000)
//            ->then([]() {dimmer.setPosition(0);})
//            ->schedule();

    while (true) {
//        PORTC |= _BV(PORTC0);
//        cpuStats.start(wallClock.now());
        auto used = taskScheduler.process();
//        cpuStats.end(wallClock.now(), used);
//        cpuStats.start(wallClock.now());
        used = eventLoop.process();
//        cpuStats.end(wallClock.now(), used);
//        PORTC &= ~ _BV(PORTC0);
    }

    return 0;
}
