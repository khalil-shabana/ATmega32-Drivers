/*
 * LCD.c
 *
 * Created: 8/1/2022 6:18:30 AM
 *  Author: Khalil
 */ 

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>
#include "LCD.h"

void LCD_APP ()
{
	u8_t CUS_PATTERN[]={
		0x15, 0x0A, 0x15, 0x0A, 0x1F, 0x15, 0x0A, 0x15,   //  1
	};
	LCD_init();
	LCD_print_char('K');
	LCD_print_char('H');
	LCD_print_char('A');
	LCD_print_char('L');
	LCD_print_char('I');
	LCD_print_char('L');
	LCD_goto_pos(0,15);
	LCD_print_string_at_XY("ALI",0,15);
	LCD_print_number_at_XY(1999,1,4);
	LCD_Generate_CUSTOM_Pattern(CUS_PATTERN,0);
	LCD_print_CUSTOM_pattern(0,1,12);
	_delay_ms(1000);
	LCD_Write_CMD(LCD_CLR_DISPLAY);
	u8_t x=0;
	while(1)
	{
		LCD_print_number_at_XY(x,1,0);
		x++;
		_delay_ms(400);
		if(x==10)
		{
			x=0;
		}
	}
}
