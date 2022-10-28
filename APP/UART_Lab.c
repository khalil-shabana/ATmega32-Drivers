/*
 * UART_Lab.c
 *
 * Created: 9/14/2022 3:54:41 AM
 *  Author: Khalil
 */ 

#include "UART.h"
#include "UART_config.h"
#include <IO_ATMEGA32.h>
#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <util/delay.h>
#include "EX_Interrupt.h"
#include "LCD.h"
#include "UART_Services.h"

void UART_App()
{
	IO_Init();
	//LCD_init();
	UART_INIT();
	
	u8_t x=1, Local_u8_UARTData, str[100]={0};
		
	UART_SEND_String("SOS");
	
	while (1)
	{	
		
		UART_RECEIVE_String(str); 
		UART_SEND_String_MyProtocol(str); 
		
		/*LCD_goto_pos(0,5);
		LCD_print_number(x);
		x++;
		if (x==10) { x=0; }
			_delay_ms(200);*/		 
	}
}