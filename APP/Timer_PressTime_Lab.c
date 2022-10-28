/*
 * Timer_PressTime_Lab.c
 *
 * Created: 9/3/2022 5:50:39 PM
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

/*------------------------ PRESS TIME APPLICATION ------------------------*/

volatile u16_t c=0 ,mili_sec=0,y,t1,t2,timer_flag=0;
u32_t x,T_total;

void PressTime_ISR()
{
	//static u8_t flag=0;
	if (timer_flag == 0)
	{
		t1=TCNT0_reg;
		c=0;
		EX_INT_TriggerEdge(EX_INT0,RISING_EDGE);
		timer_flag=1;
	}
	else
	{
		t2=TCNT0_reg;
		EX_INT_TriggerEdge(EX_INT0,FALLING_EDGE);
		timer_flag=2;
		TIMER0_OV_INT_Disable();//to save c value
	}
}
void timer_press_time()
{
	IO_Init();
	LCD_init();
	LCD_print_string_at_XY("Press Time",0,0);
	EX_INT_TriggerEdge(EX_INT0,FALLING_EDGE);
	EX_INT_Set_Call_Back(EX_INT0, PressTime_ISR);
	EX_INT_Enable(EX_INT0);
	
	TIMER0_INIT(TIMER0_NORMAL_MODE,TIMER0_SCALER_8, TIMER0_OC_DISCONNECTED);
	TIMER0_OV_INT_Enable();
	sei();
	while (1)
	{
		LCD_print_number_at_XY(x,1,0);
		_delay_ms(300);
		x++;
		if (x==10) {x=0;}
		
		if (timer_flag==2)
		{
			T_total= (t2-t1 +((u32_t)c*256))/1000;
			LCD_print_string_at_XY(" --> ",1,3);
			LCD_goto_pos(1,3);
			LCD_print_number(T_total/1000);
			LCD_print_char('.');			LCD_print_number(T_total%1000);
			TIMER0_OV_INT_Enable();
			timer_flag=0;
		}
	}
}

ISR (TIMER0_OVF_vector)
{
	c++;
}