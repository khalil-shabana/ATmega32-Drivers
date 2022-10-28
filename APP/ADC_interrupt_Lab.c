/*
 * ADC_interrupt_Lab.c
 *
 * Created: 9/3/2022 3:07:34 AM
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


u8_t ADC_LocalFlag =0;

void ADC_Complete_ISR (void)
{
	ADC_LocalFlag++;
}
void ADC_Interrupt_App()
{
	IO_Init();
	LCD_init();
	ADC_INIT(); //Free running mode activated
	
	ADC_INTERRUPT_ENABLE();
	sei();
	
	LCD_print_string_at_XY("ADC Lap",0,0);
	
	ADC_SET_CALL_BACK(ADC_Complete_ISR);
	ADC_START_CON(ADC_Channel0);
	
	while (1)
	{
		if (ADC_LocalFlag ==1)
		{
			u16_t Local_u16ConValue2 = ADC_GET_RESULT();
			LCD_print_string_at_XY("				",1,0);
			LCD_print_number_at_XY(Local_u16ConValue2,1,0);
			_delay_ms(300);
			ADC_LocalFlag=0;
		}
	}
	
}