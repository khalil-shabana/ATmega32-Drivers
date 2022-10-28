/*
 * Seven_SEG.c
 *
 * Created: 7/31/2022 2:18:14 AM
 *  Author: Khalil
 */ 
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "Seven_Segment.h"
#include <avr/io.h>
#include <util/delay.h>

void SEV_SEG(u8_t num)
{
	seven_seg_init();
	while(1)
	{
		if (num < 100)
		{
			u8_t right = num % 10;
			u8_t left = num / 10;
			seven_seg_Disable1();
			seven_seg_Disable2();
			seven_seg_write(left);
			seven_seg_Enable1();
			_delay_ms(5);
			seven_seg_Disable1();
			seven_seg_write(right);
			seven_seg_Enable2();
			_delay_ms(5);
			
		}
	}
	/*DDRA=0xff;
	while(1)
	{
		PORTA = ~(0b00111111);
	}*/
}