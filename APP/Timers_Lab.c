/*
 * Timers_LAP.c
 *
 * Created: 8/16/2022 3:42:03 PM
 *  Author: Khalil
 */ 
#include <IO_ATMEGA32.h>
#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <util/delay.h>
#include "EX_Interrupt.h"
#include "Timer.h"
#include "LCD.h"
#include "ADC.h"
#include "Timer_Services.h"

u16_t Local_u16_x=0,Local_u16_adc,Local_u16_duty;
u32_t Local_u32_freq;


void timer_func()
{
	sei();
	IO_Init();	
	LCD_init();
	ADC_INIT();
	TIMER1_INIT(TIMER1_NORMAL_MODE,TIMER1_SCALER_8,TIMER1_OC1A_DISCONNECTED,TIMER1_OC1B_INVERTING);
	
	LCD_print_string("freq:");
	LCD_goto_pos(1,0);
	LCD_print_string("duty:");
	
	while (1)
	{
		PWM_Measuring(&Local_u32_freq,&Local_u16_duty);
		LCD_goto_pos(0,6);
		LCD_print_number(Local_u32_freq);
		LCD_goto_pos(1,6);
		LCD_print_number(Local_u16_duty);
		
	}
}




