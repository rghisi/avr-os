#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Packet.h"
#include "PacketFactory.h"

PacketFactory packetFactory = PacketFactory();
Packet packet = Packet();

void send() {
	//Enable interrupt
	UCSR1B |= (1 << UDRIE1);
}

ISR(USART1_UDRE_vect) {
	if (!packet.hasNext() && packetFactory.hasNextPacket()) {
		packet = packetFactory.nextPacket();
	}
	if (packet.hasNext()) {
		UDR1 = packet.next();
	} else {
		//Disable Interrupt
		UCSR1B &= ~(1 << UDRIE1);
	}
}

int main(void) {
	//9600bps
	UBRR1 = 0x067;
	//8bit no parity one stop
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
	//enable RX and TX
	UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << UDRIE1);

	DDRB |= (1 << DDB0);
	sei();

	uint8_t data[] =
			"ABCDEFGHIJKLMNOPQRSTUVXZABCDEFGHIJKLMNOPQRSTUVXZABCDEFGHIJKLMNOPQRSTUVXZABCDEFGHIJKLMNOPQRSTUVXZABCDEFGHIJKLMNOPQRSTUVXZABCDEFGHIJKLMNOPQRSTUVXZABCDEFGHIJKLMNOPQRSTUVXZABCDEFGHIJKLMNOPQRSTUVXZABCDEFGHIJKLMNOPQRSTUVXZABCDEFGHIJKLMNOPQRSTUVXZABCDEFGHIJklmnopqrstuvxzabcdefghijklmnopqrstuvxzabcdefghijklmnopqrstuvxzabcdefghijklmnopqrstuvxzabcdefghijklmnopqrstuvxzabcdefghijklmnopqrstuvxz";
	uint16_t dataSize = sizeof(data);
	packetFactory.prepare(0x08, 0x0F, data, dataSize);

	send();
	while (1) {
		PORTB ^= 0xFF;
		_delay_ms(500);
	}

	return 0;
}

