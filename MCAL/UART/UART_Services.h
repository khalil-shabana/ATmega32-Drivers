/*
 * UART_Services.h
 *
 * Created: 9/14/2022 6:35:36 AM
 *  Author: Khalil
 */ 
#include "UART.h"

#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

/************* Sending string *************/
void UART_SEND_String(u8_t* uart_string);
void UART_RECEIVE_String(u8_t* uart_string);

/************* Sending string using special Protocol *************/
void UART_SEND_String_MyProtocol(u8_t* uart_string);
u8_t UART_RECEIVE_String_MyProtocol(u8_t* uart_string);

/******************* Send string Asynchrouns (using interrupt) *******************/
void UART_SEND_String_Asynch(u8_t* uart_string);
void UART_RECEIVE_String_Asynch(u8_t* uart_string);


#endif /* UART_SERVICES_H_ */