/*
 * GccApplication2.c
 *
 * Created: 12.01.2023 22:05:18
 * Author : pavel Kobiela
 */ 

#define F_CPU 16000000L // Specify oscillator frequency
#include <avr/io.h>
#include <util/delay.h>

#define PORTB_CYFRA_0 0b00011011
#define PORTD_CYFRA_0 0b11100000
#define PORTB_CYFRA_1 0b00010000
#define PORTD_CYFRA_1 0b01100000
#define PORTB_CYFRA_2 0b00011101
#define PORTD_CYFRA_2 0b10100000
#define PORTB_CYFRA_3 0b00111100
#define PORTD_CYFRA_3 0b11100000
#define PORTB_CYFRA_4 0b00010110
#define PORTD_CYFRA_4 0b01100000
#define PORTB_CYFRA_5 0b00001110
#define PORTD_CYFRA_5 0b11100000
#define PORTB_CYFRA_6 0b00001111
#define PORTD_CYFRA_6 0b11100000
#define PORTB_CYFRA_7 0b00011000
#define PORTD_CYFRA_7 0b01100000
#define PORTB_CYFRA_8 0b00011111
#define PORTD_CYFRA_8 0b11100000
#define PORTB_CYFRA_9 0b00011110
#define PORTD_CYFRA_9 0b11100000

int main(void)
{
	DDRB = 0xff;	//	output
	DDRD = 0xff;	//	output
	//DDRC = 0x00;		//	input
	//DDRB = 0b10000000; // configure pin 7 of PORTB as output (digital pin 13 on the Arduino Mega2560)
	PORTB = 0x00;	// PORTB - 0 configured as an output
	PORTD = 0x00;
	//PORTC = 0x00;
	
	DDRC = DDRC & (~(1<<0));		/* Make PD2 as input pin */
	PORTC = PORTC | (1<<0);			/* Enable pull-up on PD2 by writing 1 to it */

		/* segments
		 a
		 ---
		|f	|b
		 --- g
		|e  |c
		 ---	.[dp]
		 d
		PORTB = 0b00bagfe
		PORTD = 0bdc[dp]00000
		
		*/
	uint8_t const _portb[10] = {PORTB_CYFRA_0, PORTB_CYFRA_1, PORTB_CYFRA_2, PORTB_CYFRA_3, PORTB_CYFRA_4, PORTB_CYFRA_5, PORTB_CYFRA_6, PORTB_CYFRA_7, PORTB_CYFRA_8, PORTB_CYFRA_9};
	uint8_t const _portd[10] = {PORTD_CYFRA_0, PORTD_CYFRA_1, PORTD_CYFRA_2, PORTD_CYFRA_3, PORTD_CYFRA_4, PORTD_CYFRA_5, PORTD_CYFRA_6, PORTD_CYFRA_7, PORTD_CYFRA_8, PORTD_CYFRA_9};
	int8_t k = 0;
	int pin_status;
	uint8_t _switchFlag = 0xff;	
	
	while(1)
	{
		if (k == 10 && _switchFlag == 0x00) {k = 0;}
		if (k < 0 && _switchFlag == 0xff) {k = 10;}
			
			PINB = 0x00;
			PIND = 0x00;
			PORTB = _portb[k];
			PORTD = _portd[k];
			_delay_ms(1000);
			PORTB = 0x00;
			PORTD = 0x00;
			

		if(_switchFlag == 0xff) {
			k--;
		}
		else {
			k++;	
		}
		
		pin_status = PINC & (1<<0);	// Read status of pin PINC0
		if(pin_status)				
		{
		    _switchFlag = 0x00;
		}
		else
		{
			_switchFlag = 0xff;
		}
	}
}