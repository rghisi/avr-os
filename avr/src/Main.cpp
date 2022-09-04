#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "hw/avr/ATMega32U4.h"
#include "Packet.h"
#include "SerialNetworkInterface.h"

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

auto *usart = new ATMega32U4();
auto networkInterface = SerialNetworkInterface(0x01, usart);

//void enableReadyToSendInterrupt() {
//	//Enable interrupt
//	UCSR1B |= (1 << UDRIE1);
//}

//TX register is empty - aka: ready to send
ISR(USART1_UDRE_vect) {
    networkInterface.handleReadyToSendInterrupt();
}

ISR(USART1_TX_vect) {
    networkInterface.handleTransmissionFinished();
}

ISR(USART1_RX_vect) {
    networkInterface.handleDataReceivedInterrupt();
}

int main(void) {
    DDRB |= (1 << DDB0);
    PORTB ^= 0xFF;
    _delay_ms(100);
    PORTB ^= 0xFF;
    _delay_ms(100);
    PORTB ^= 0xFF;
    _delay_ms(1000);

    //9600bps
    UBRR1 = 0x067;
    //8bit no parity one stop
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);

	sei();

	uint8_t data[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	uint8_t dataSize = sizeof(data);
    uint8_t id = 0;

    auto* packet1 = new Packet(0x02, 0x01, 0x01, 0x01, 0x00, data, dataSize);
    networkInterface.pushToSendQueue(packet1);
    auto* packet2 = new Packet(0x02, 0x01, 0x02, 0x01, 0x00, data, dataSize);
    networkInterface.pushToSendQueue(packet2);
    auto* packet3 = new Packet(0x02, 0x01, 0x03, 0x01, 0x00, data, dataSize);
    networkInterface.pushToSendQueue(packet3);

    while (1) {
        if (networkInterface.receiveQueueHasPackets()) {
            auto* receivedPacket = networkInterface.popFromReceiveQueue();
            if (receivedPacket->checkCrc()) {
                networkInterface.pushToSendQueue(receivedPacket);
                PORTB ^= 0xFF;
            } else {
                PORTB ^= 0xFF;
                _delay_ms(500);
                PORTB ^= 0xFF;
                _delay_ms(500);
                PORTB ^= 0xFF;
                _delay_ms(500);
                PORTB ^= 0xFF;
                _delay_ms(500);
                PORTB ^= 0xFF;
                _delay_ms(500);
                PORTB ^= 0xFF;
                _delay_ms(500);
                PORTB ^= 0xFF;
                return 0;
            }

        }
        if (id == 0xFF) {
            PORTB = 0x00;
            _delay_ms(2000);
        }
        PORTB ^= 0xFF;
//        _delay_ms(500);
	}

	return 0;
}

