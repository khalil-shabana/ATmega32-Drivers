/*
 * Interrupt_LAP.c
 *
 * Created: 8/10/2022 3:42:37 PM
 *  Author: Khalil
 */ 
#include "ATmega32_Registers.h"
#include <IO_ATMEGA32.h>
#ifndef F_CPU
#define F_CPU 8000000UL
#endif


#include <util/delay.h>
#include "LCD.h"
#include "EX_Interrupt.h"
void EX_INT_Set_Call_Back(EX_INT_Source_t INT_Source, void (*Local_ptr)(void));

u8_t flag =0;
void Func1(void)
{
	//LCD_print_string("ahmed",0,0);
	flag =1;
}
void Func2(void)
{
	TOGGLE_BIT(PORTB_reg,PIN_1);
	//LCD_print_string("ayman",0,0);
	//_delay_ms(2000);
}
void Func3(void)
{
	TOGGLE_BIT(PORTB_reg,PIN_3);
	//LCD_print_string("					",0,0);
}

void EX_INT()
{
	sei(); //open global interrupt
	//cli();  //close global interrupt
	
	DDRB_reg=0b11111011;
	DDRD_reg=0b00000100;
	PORTB_reg=0b00000000;
	
	LCD_init();
		
	EX_INT_TriggerEdge(EX_INT0,RISING_EDGE);
	EX_INT_TriggerEdge(EX_INT1,FALLING_EDGE);
	EX_INT_TriggerEdge(EX_INT2,RISING_EDGE);
	EX_INT_Enable(EX_INT0);
	EX_INT_Enable(EX_INT1);
	EX_INT_Enable(EX_INT2);
	
	EX_INT_Set_Call_Back(EX_INT0,Func1);
	//EX_INT_Set_Call_Back(EX_INT1,Func2);
	//EX_INT_Set_Call_Back(EX_INT2,Func3);
	
	LCD_print_string_at_XY("Hello!",0,0);
	_delay_ms(1000);
	LCD_print_string_at_XY("Test1",0,0);
	//sei();
	u8_t x=0;
	while(1)
	{
		LCD_print_number_at_XY(x,1,0);
		x++;
		_delay_ms(500);
		if (x==5)
		{
			EX_INT_Set_Call_Back(EX_INT0,Func2);
			//IO_WritePinVal(GROUP_D,PIN_2,HIGH);
			//_delay_ms(50);
		}
				
		if (x==10)
		{
			x=0;
			EX_INT_Set_Call_Back(EX_INT0,Func3);
		}
		if (flag==1)
		{
			TOGGLE_BIT(PORTB_reg,PIN_0);
			flag=0;
		}
/*------Reentrant Function & Non-Reentrant Function------*/
		//cli();
		//LCD_print_string_at_XY("hosam",1,0);
		//sei();
		//i'll go to ISR and make interrupt that write on LCD
/*--------------------------------------------------*/
		/*if(IO_GetPinVal(GROUP_D,PIN_2))
		{
			TOGGLE_BIT(PORTB_reg,0);
			while(IO_GetPinVal(GROUP_D,PIN_2));
		}
	
		if (!IO_GetPinVal(GROUP_D,PIN_3))
		{
			TOGGLE_BIT(PORTB_reg,1);
			while(!IO_GetPinVal(GROUP_D,PIN_3));
		}*/
		
	}
	
}

/*ISR (INT0_vector)
{
	//here we are trying to re-open global interrupt ;as the interrupt \
	before execution closes the global interrupt to prevent \
	any another interrupt to interrupt him. So we open global interrupt to allow another interrupts\
	to interrupt the current one
	
	//_delay_ms(2000);
	LCD_print_string_at_XY("ahmed",0,0);
	TOGGLE_BIT(PORTB_reg,PIN_0);
}

ISR (INT1_vector)
//ISR (INT1_vector,ISR_NOBLOCK)
//this second predefined argument: re-open global interrupt
{ 
	TOGGLE_BIT(PORTB_reg,PIN_1);
	LCD_print_string_at_XY("ayman",0,0);
	//_delay_ms(2000);
}
ISR(INT2_vector)
{
	LCD_print_string_at_XY("					",0,0);
}
ISR (BAD_vector)
{
	TOGGLE_BIT(PORTB_reg,PIN_7);
}*/