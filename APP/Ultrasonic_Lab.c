/*
 * Ultrasonic_Lab.c
 *
 * Created: 9/12/2022 1:25:45 AM
 *  Author: Khalil
 */ 
#include <IO_ATMEGA32.h>
#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <util/delay.h>
#include "Timer.h"
#include "LCD.h"
#include "EX_Interrupt.h"
#include "Ultrasonic.h"

void ultrasonic_APP()
{
	sei();
	IO_Init(); //trig pin -> input //Echo pin -> o/p connected to ICP1 pin
	LCD_init();
	ULTRASONIC_INIT();
	u16_t distance;
	
	while(1)
	{
		distance = ULTRASONIC_GET_DISTANCE(ULTRASONIC_1);
		LCD_goto_pos(0,6);
		LCD_print_number(distance);
	}
}