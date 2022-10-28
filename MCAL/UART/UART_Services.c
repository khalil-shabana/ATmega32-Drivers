/*
 * UART_Services.c
 *
 * Created: 9/14/2022 6:35:15 AM
 *  Author: Khalil
 */ 

#include "UART_Services.h"
#include "LCD.h"

/******************* Variables *******************/
static volatile  u8_t Uart_Service_flag=1;
static u8_t  *Asynch_Send_Str;
static u8_t  *Asynch_receive_str;

/************* Sending string *************/

 void UART_SEND_String(u8_t* uart_string)
 {
	 u8_t i=0;
	 while (uart_string[i] != '\0')
	 {
		 UART_SEND_BYTE(uart_string[i]);
		// _delay_us(1);
		 i++;
	 }
 }
 
// Receive function
 void UART_RECEIVE_String(u8_t* uart_string)
 {
	 u8_t i=0;
	 uart_string[i]= UART_RECEIVE_BYTE();
	 while (uart_string[i] != 0x0d)
	 {
		 i++;
		 uart_string[i]= UART_RECEIVE_BYTE();
	 }
	 uart_string[i] = '\0';
 }
 
 /************* Sending string using special Protocol *************/
 
 void UART_SEND_String_MyProtocol(u8_t* uart_string)
 {
	 u8_t i=0, length=0;
	 u16_t sum=0;
	 while (uart_string[length] != '\0')
	 {
		 sum+=uart_string[length];
		 length++;
	 }
	 UART_SEND_BYTE(length);
	 for (i=0;i<length;i++)
	 {
		 UART_SEND_BYTE(uart_string[i]);
	 }
	 UART_SEND_BYTE((u8_t)sum);
	 UART_SEND_BYTE((u8_t)(sum>>8));
	 
 }
 
 // Receive function
 u8_t UART_RECEIVE_String_MyProtocol(u8_t* uart_string)
 {
	 u8_t length=0, i=0, low_byte=0, high_byte=0;
	 u16_t sum_cal=0, sum_received=0;
	 
	 length = UART_RECEIVE_BYTE(uart_string);
	 
	 for (i=0;i<length;i++)
	 {
		uart_string[i]= UART_RECEIVE_BYTE(); 
		sum_cal+= uart_string[i];
	 }
	 low_byte = UART_RECEIVE_BYTE();
	 high_byte= UART_RECEIVE_BYTE();
	 sum_received= low_byte | (high_byte<<8);
	 
	 //////////// Test code //////////////
	 LCD_print_number(length);
	 LCD_print_number(sum_cal);
	 LCD_print_number(sum_received);
	////////////////////////////////////// 
	 //Check sum test
	 if (sum_received == sum_cal)
		 return 1;
	else
		 return 0;
 }
 
/******************* Send string Asynchrouns (using interrupt) *******************/
static void TX_ISR_Func ()
{
	static u8_t i = 1;
	if (Asynch_Send_Str != '\0')
	{
		UART_SEND_BYTE_WITH_INT(Asynch_Send_Str[i]);
		i++;
	}
	else
	{
		i = 1;
		UART_TX_INT_Disable();
	}
}

void UART_SEND_String_Asynch(u8_t* uart_string)
{
	UART_TX_INT_Enable();
	Asynch_Send_Str =uart_string;
	UART_SEND_BYTE(uart_string[0]);
	UART_TX_SetCallBack(TX_ISR_Func);
}


// Receive function
static void RX_ISR_Func()
{
	static u8_t i =0;
	Asynch_receive_str[i] = UART_RECEIVE_BYTE_WITH_INT();
	i++;
}

void UART_RECEIVE_String_Asynch(u8_t* uart_string)
{
	UART_RX_INT_Enable();
	Asynch_receive_str = uart_string;
	UART_RX_SetCallBack(RX_ISR_Func);
}

