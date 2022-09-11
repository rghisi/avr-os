#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "hw/avr/ATMega32U4.h"
#include "networking/Packet.h"
#include "networking/SerialNetworkInterface.h"
#include "std/Random.h"
#include "network-services/NetworkServices.h"
#include "network-services/Ping.h"

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

//ISR(USART1_UDRE_vect) {
//    networkInterface.handleReadyToSendInterrupt();
//}
//
//ISR(USART1_TX_vect) {
//    networkInterface.handleTransmissionFinished();
//}
//
//ISR(USART1_RX_vect) {
//    networkInterface.handleDataReceivedInterrupt();
//}

void setupRandom() {
    DIDR0 |= (1 << ADC7D);
    DIDR0 = 0xFF;
    DIDR1 = 0xFF;
    DIDR2 = 0xFF;
    ADMUX = (1 << REFS1) | (1 << REFS0);
    ADMUX |= (0 << MUX4) | (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0);
    ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0));
    ADCSRB &= ~((1 << ADTS3) | (1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0));
    ADCSRA |= (1 << ADATE) | (1 << ADEN);
    ADCSRA |= (1 << ADSC);
    _delay_ms(500);
    Random::seed(ADCL);
}

int main(void) {
    DDRB |= (1 << DDB0);
    PORTB = 0x00;
    _delay_ms(100);
    PORTB = 0xFF;
    _delay_ms(1000);

    setupRandom();

    auto *usart = new ATMega32U4(ATMega32U4::BitRate::B9600);
    auto *networkInterface = new SerialNetworkInterface(0xAB, usart);
    usart->setInterruptHandler(networkInterface);

    auto *networkServices = new NetworkServices(networkInterface);
    auto *ping = new Ping(networkServices);

    networkServices->addReceiver(ping);

    sei();

//	uint8_t data1[] = {'A', Random::next(), ADCL};
//    uint8_t dataSize = sizeof(data1);
//    uint8_t data2[] = {'B', Random::next(), ADCL};
//    uint8_t data3[] = {'C',Random::next(), ADCL};
//    uint8_t id = 0;

//    auto* packet1 = new Packet(0x02, 0x01, 0x01, 0x01, 0x00, data1, dataSize);
//    networkInterface->pushToSendQueue(packet1);
//    auto* packet2 = new Packet(0x02, 0x01, 0x02, 0x01, 0x00, data2, dataSize);
//    networkInterface->pushToSendQueue(packet2);
//    auto* packet3 = new Packet(0x02, 0x01, 0x03, 0x01, 0x00, data3, dataSize);
//    networkInterface->pushToSendQueue(packet3);
//    usart->disableReceiver();
    usart->enableTransmitterAndReadyToSendInterrupt();

//    UDR1 = 'E';
    while (1) {
//        UDR1 = 'F';
//        PORTB ^= 0xFF;
        _delay_ms(1000);
//        UDR1 = '1';
//        networkServices->processReceiveQueue();
//        PORTB ^= 0xFF;
//        _delay_ms(200);
//        ping->ping(0xAB);
//        networkServices->processSendQueue();
//        PORTB ^= 0xFF;

//        _delay_ms(100);
//        UDR1 = '.';
        _delay_ms(1000);
	}

	return 0;
}

