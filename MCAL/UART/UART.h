/*
 * UART.h
 *
 * Created: 9/13/2022 12:16:38 AM
 *  Author: Khalil
 */ 


#ifndef UART_H_
#define UART_H_

#include "Data_types.h"
#include "Bit_Mask.h"
#include "ATmega32_Registers.h"

void UART_INIT(void);

/*************************** Send and receive functions with polling ***************************/
void UART_SEND_BYTE(u8_t uart_data);
u8_t UART_RECEIVE_BYTE();

u8_t UART_SEND_BYTE_NO_WAIT(u8_t uart_data);
u8_t UART_RECEIVE_BYTE_NO_WAIT(u8_t* pData);

/*****************************************Interrupt functions*********************************************/
void UART_RX_INT_Enable(void);
void UART_RX_INT_Disable(void);

void UART_TX_INT_Enable(void);
void UART_TX_INT_Disable(void);

/*************************** Set call-back functions ***************************/
void UART_TX_SetCallBack(void (*Local_Fptr) (void));
void UART_RX_SetCallBack(void (*Local_Fptr) (void));

/*************************** Send and receive functions using interrupt ***************************/
void UART_SEND_BYTE_WITH_INT(u8_t uart_data);
u8_t UART_RECEIVE_BYTE_WITH_INT(void);

#endif /* UART_H_ */