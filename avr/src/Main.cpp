#include <cstdlib>
#include "../avr-libstdcpp/src/functexcept.cc"
#include "../avr-libstdcpp/src/list.cc"

#include "hw/avr/ATMega328P.h"
#include "system/TaskScheduler.h"
#include "system/EventLoop.h"
#include "system/Messaging.h"
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
#include "time/TimeTicker.h"
#include "app/TimedDrying.h"
#include "app/ApplicationManager.h"
#include "app/TimedMultiTrayDrying.h"

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
auto wallClock = WallClock();
auto taskScheduler = TaskScheduler(&wallClock);
auto subscriberRegistry = SubscriberRegistry();
auto eventLoop = EventLoop(&subscriberRegistry);
auto messaging = Messaging(&eventLoop);
auto timer = Timer(&messaging, &wallClock);
auto asyncExecutor = AsyncExecutor(&taskScheduler, &messaging);
auto display = Display();
//auto periodicMemoryReport = PeriodicMemoryReport(&messaging);
auto keyPad = KeyPad(&messaging);
auto dial = Dial(&messaging);
auto periodicSensorReport = PeriodicSensorReport(&messaging);
auto dimmer = Dimmer(&atmega, &atmega);
auto timeTickTask = TimeTicker(&messaging, &wallClock);
auto temperatureControl = TemperatureControl(&messaging, &dimmer);

auto timedDrying = TimedDrying(&messaging, &timer);
auto timedMultiTrayDrying = TimedMultiTrayDrying(&messaging);
auto test = Test(&messaging, &dimmer);
auto applicationManager = ApplicationManager(&messaging, {&timedDrying, &timedMultiTrayDrying, &test});

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

    subscriberRegistry.subscribe(&timer, TIME_TICK);
    subscriberRegistry.subscribe(&asyncExecutor, ASYNC_SCHEDULED);
    subscriberRegistry.subscribe(&asyncExecutor, ASYNC_CHAIN_SCHEDULED);
    subscriberRegistry.subscribe(&display, DISPLAY_COMMAND);
    subscriberRegistry.subscribe(&applicationManager, USER_INPUT);
    subscriberRegistry.subscribe(&timedDrying, TIMER_STATE);
    subscriberRegistry.subscribe(&timedDrying, USER_INPUT);
    subscriberRegistry.subscribe(&timedDrying, CLIMATE_REPORT);
    subscriberRegistry.subscribe(&timedDrying, TEMPERATURE_CONTROL_STATUS);
    subscriberRegistry.subscribe(&timedMultiTrayDrying, TIME_TICK);
    subscriberRegistry.subscribe(&timedMultiTrayDrying, USER_INPUT);
    subscriberRegistry.subscribe(&timedMultiTrayDrying, CLIMATE_REPORT);
    subscriberRegistry.subscribe(&timedMultiTrayDrying, TEMPERATURE_CONTROL_STATUS);
    subscriberRegistry.subscribe(&temperatureControl, CLIMATE_REPORT);
    subscriberRegistry.subscribe(&temperatureControl, TEMPERATURE_CONTROL_COMMAND);
    subscriberRegistry.subscribe(&test, USER_INPUT);

//    taskScheduler.schedule(&periodicMemoryReport);
    taskScheduler.schedule(&keyPad);
    taskScheduler.schedule(&dial);
    taskScheduler.schedule(&periodicSensorReport);
    taskScheduler.schedule(&timeTickTask);
    taskScheduler.schedule(&temperatureControl);

    auto *startupTasks = new AsyncChain(&messaging);
    startupTasks
            ->then([]() {applicationManager.start();})
            ->schedule();



//    auto *dimmerCalibrationTask = new AsyncChain(&messaging);
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

//    auto *startTimedDrying = new AsyncChain(&messaging);
//    startTimedDrying
//            ->wait(1000)
//            ->then([]() {timedDrying.toForeground();})
//            ->wait(32000)
//            ->wait(32000)
//            ->then([]() {timedDrying.stop();})
//            ->wait(10000)
//            ->then([]() {timedDrying.toForeground();})
//            ->schedule();

    while (true) {
        taskScheduler.process();
        eventLoop.process();
    }

    return 0;
}
