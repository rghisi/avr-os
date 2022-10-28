#include <avr/io.h>
#include <util/delay.h>
#include <cstdlib>
#include "../avr-libstdcpp/src/functexcept.cc"
#include "../avr-libstdcpp/src/list.cc"

#include "hw/avr/ATMega32U4.h"
#include "network-interfaces/SerialNetworkInterface.h"
#include "network-services/NetworkServices.h"
#include "network-services/Ping.h"
#include "system/TaskScheduler.h"
#include "tasks/PeriodicPing.h"
#include "system/EventLoop.h"
#include "system/EventDispatcher.h"
#include "system/WallClock.h"
#include "tasks/PeriodicCpuUsageReport.h"
#include "system/CpuStats.h"
#include "lcd/Display.h"
#include "tasks/AsyncTaskTest.h"
#include "system/AsyncExecutor.h"
#include "tasks/PeriodicMemoryReport.h"

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

//void setupRandom() {
//    DIDR0 |= (1 << ADC7D);
//    DIDR0 = 0xFF;
//    DIDR1 = 0xFF;
//    DIDR2 = 0xFF;
//    ADMUX = (1 << REFS1) | (1 << REFS0);
//    ADMUX |= (0 << MUX4) | (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0);
//    ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0));
//    ADCSRB &= ~((1 << ADTS3) | (1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0));
//    ADCSRA |= (1 << ADATE) | (1 << ADEN);
//    ADCSRA |= (1 << ADSC);
//    _delay_ms(500);
//    Random::seed(ADCL);
//}

auto display = Display();
auto cpuStats = CpuStats();
auto atmega32U4 = ATMega32U4(ATMega32U4::BitRate::B9600);
auto wallClock = WallClock();
auto taskScheduler = TaskScheduler(&wallClock);
auto eventLoop = EventLoop();
auto eventDispatcher = EventDispatcher(&eventLoop);
auto asyncExecutor = AsyncExecutor(&taskScheduler, &eventDispatcher);
//auto networkInterface = SerialNetworkInterface(0xAB, &atmega32U4, &eventDispatcher);
//auto networkServices = NetworkServices(&eventDispatcher);
//auto ping = Ping(&eventDispatcher);
auto periodicCpuUsageReport = PeriodicCpuUsageReport(&cpuStats, &eventDispatcher);
auto periodicMemoryReport = PeriodicMemoryReport(&wallClock, &eventDispatcher);
//auto periodicPing = PeriodicPing(&ping);
auto asyncTest = AsyncTaskTest(&eventDispatcher);

int main(void) {
    uint8_t rxLed = _BV(PORTB0);
    uint8_t txLed = _BV(PORTD5);
    DDRB |= rxLed;
    DDRD |= txLed;

    //on
    PORTB &= ~rxLed;
    _delay_ms(250);
    PORTD &= ~txLed;
    _delay_ms(250);

    atmega32U4.disableReadyToSendInterrupt();
    atmega32U4.disableTransmitter();
    atmega32U4.disableReceiver();
    sei();

    atmega32U4.setTimer0InterruptHandler(&wallClock);
//    atmega32U4.setInterruptHandler(&networkInterface);
//    eventLoop.addHandler(&networkInterface);
//    eventLoop.addHandler(&networkInterface, EventType::FRAME_RECEIVED);
//    eventLoop.addHandler(&networkServices);
//    eventLoop.addHandler(&ping);
    eventLoop.addHandler(&asyncExecutor);
    eventLoop.addHandler(&asyncExecutor, ASYNC_CHAIN_SCHEDULED);
    eventLoop.addHandler(&display);
    eventLoop.addHandler(&display, SHOW_TEXT_REQUESTED);
    eventLoop.addHandler(&display, MEMORY_STATS_DISPATCHED);

//    taskScheduler.schedule(&periodicPing);
    taskScheduler.schedule(&periodicCpuUsageReport);
    taskScheduler.schedule(&periodicMemoryReport);
    taskScheduler.schedule(&asyncTest);

//    atmega32U4.enableReceiver();

    while (true) {
        cpuStats.start(wallClock.now());
        auto used = taskScheduler.process();
        cpuStats.end(wallClock.now(), used);
        cpuStats.start(wallClock.now());
        used = eventLoop.process();
        cpuStats.end(wallClock.now(), used);
	}

	return 0;
}
