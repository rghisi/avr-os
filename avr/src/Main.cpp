#include <cstdlib>
#include "../avr-libstdcpp/src/functexcept.cc"
#include "../avr-libstdcpp/src/list.cc"

#include "hw/avr/ATMega328P.h"
#include "system/TaskScheduler.h"
#include "system/EventLoop.h"
#include "system/Messaging.h"
#include "system/WallClock.h"
#include "lcd/Display.h"
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
#include "comms/Serial.h"
#include "services/SerialReporter.h"

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
auto serial = Serial(&atmega);
auto display = Display();
auto periodicMemoryReport = PeriodicMemoryReport(&messaging);
auto keyPad = KeyPad(&messaging);
auto dial = Dial(&messaging);
auto serialReporter = SerialReporter(&messaging);
auto periodicSensorReport = PeriodicSensorReport(&messaging);
auto dimmer = Dimmer(&atmega, &atmega);
auto timeTickTask = TimeTicker(&messaging, &wallClock);
auto temperatureControl = TemperatureControl(&messaging, &dimmer);

auto timedDrying = TimedDrying(&messaging, &timer);
auto timedMultiTrayDrying = TimedMultiTrayDrying(&messaging);
auto test = Test(&messaging, &dimmer);
auto applicationManager = ApplicationManager(&messaging, {&timedDrying, &timedMultiTrayDrying, &test});

int main(void) {
    atmega.setInterruptHandler(&serial);
    atmega.enableTransmitterAndReadyToSendInterrupt();
    atmega.setupTimer0();
    atmega.setTimer0InterruptHandler(&wallClock);
    atmega.setupTimer1();
    atmega.setTimer1CompareMatchAInterruptHandler(&dimmer);
    atmega.setupExternalInterrupt();
    atmega.setExternalInterruptHandler(&dimmer);
    atmega.enableInterrupts();

    keyPad.setup();
    dial.setup();

    subscriberRegistry.subscribe(&serial, SERIAL_SEND);
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
    subscriberRegistry.subscribe(&serialReporter, CLIMATE_REPORT);
    subscriberRegistry.subscribe(&serialReporter, TEMPERATURE_CONTROL_STATUS);
    subscriberRegistry.subscribe(&serialReporter, MEMORY_REPORT);

    taskScheduler.schedule(&periodicMemoryReport);
    taskScheduler.schedule(&keyPad);
    taskScheduler.schedule(&dial);
    taskScheduler.schedule(&periodicSensorReport);
    taskScheduler.schedule(&timeTickTask);
    taskScheduler.schedule(&temperatureControl);
    taskScheduler.schedule(&serialReporter);

    applicationManager.start();

    while (true) {
        taskScheduler.process();
        eventLoop.process();
    }

    return 0;
}
