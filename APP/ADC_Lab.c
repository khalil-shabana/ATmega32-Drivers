/*
 * ADC_Lap.c
 *
 * Created: 8/31/2022 7:15:17 PM
 *  Author: Khalil
 */ 

#include "Data_types.h"
#include "Bit_Mask.h"
#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <util/delay.h>
#include "IO_ATMEGA32.h"
#include "LCD.h"
#include "EX_Interrupt.h"
#include "ADC.h"


/*
ISR(ADC_vector)
{
	ADCSRA_reg |= 1<<6; // ADC start conversion
	LCD_print_number_at_XY(ADCH_reg,1,0);
	LCD_print_number_at_XY(ADCL_reg,1,2);
}*/
void ADC_func()
{
	u16_t Local_u16ConValue;
	IO_Init();
	LCD_init();
	ADC_INIT();
	sei();
	LCD_print_string_at_XY("ADC Lap",0,0);
	IO_PinVal_t CurrentState = HIGH; //pulled up
	IO_PinVal_t PreviousState= HIGH;
	
	while (1)
	{
		CurrentState = IO_GetPinVal(GROUP_D,PIN_2);
		if (PreviousState==HIGH && CurrentState==LOW)
		{
			ADC_START_CON(ADC_Channel0);
			Local_u16ConValue= ADC_GET_RESULT();
			//LCD_goto_pos(1,0);
			LCD_print_number_at_XY(Local_u16ConValue,1,0);
		} 
		else if (PreviousState==LOW && CurrentState==HIGH)
		{
			LCD_print_string_at_XY("				",1,0);
		}
		PreviousState = CurrentState;
	}
	
}