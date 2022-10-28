/*
 * LED.c
 *
 * Created: 7/31/2022 1:41:01 AM
 *  Author: Khalil
 */ 

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "IO_ATMEGA32.h"

void LED()
{
	//IO_Init();
	IO_WritePinDir(GROUP_D,PIN_0,OUTPUT);
	IO_WritePinVal(GROUP_D,PIN_0,LOW);
	IO_WritePinDir(GROUP_D,PIN_6,INPUT);
	SET_BIT(PORTD_reg,PIN_6);
	while (1)
	{
		if(!IO_GetPinVal(GROUP_D,PIN_6))
		{
			TOGGLE_BIT(PORTD_reg,PIN_0);
			_delay_ms(1000);
		}
	}
		
	
/*
IO_WritePinDir(GROUP_D,PIN_5,OUTPUT);
 IO_WritePinDir(GROUP_D,PIN_6,OUTPUT);
  IO_WritePinDir(GROUP_D,PIN_7,OUTPUT);
   
   IO_WritePinVal(GROUP_D,PIN_5,HIGH);
   _delay_ms(1000);
   IO_WritePinVal(GROUP_D,PIN_6,HIGH);
   _delay_ms(1000);
   IO_WritePinVal(GROUP_D,PIN_7,HIGH);*/
}