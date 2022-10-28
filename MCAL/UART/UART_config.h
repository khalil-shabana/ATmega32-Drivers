/*
 * UART_config.h
 *
 * Created: 9/13/2022 1:09:59 AM
 *  Author: Khalil
 */ 


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/********************************* UART configuration *********************************/
#define SPEED				NORMAL_SPEED
#define CPU_F				_8_MHZ
#define BUAD_RATE			_9600
#define SYNC_MODE			ASYNCH
#define PARITY_MODE			NO_PARITY
#define NO_DATA_BITS		_8_DATA_BITS
#define NO_STOP_BITS		ONE_STOP_BIT

/******************** SPEED MODES *************************/
#define NORMAL_SPEED	0
#define DOUBLE_SPEED	1
#define SPEED_MODES		2

/******************** CPU_F *************************/
#define   _4_MHZ         0
#define   _8_MHZ         1
#define  _16_MHZ         2
#define  TOTAL_CPU_F     3

/******************* BAUD RATE *****************************/
#define _2400		0
#define _4800		1
#define _9600		2
#define _14400		3
#define _19200		4
#define _28800		5
#define  TOTAL_BAUD_RATE 6

/*************** Sync. mode *************************/
#define  SYNCH  0
#define  ASYNCH 1

/******************* Parity mode *************************/
#define NO_PARITY    0
#define EVEN_PARITY  1
#define ODD_PARITY   2

/*************** # of data bits ********************/
#define  _5_DATA_BITS    5
#define  _6_DATA_BITS    6
#define  _7_DATA_BITS    7
#define  _8_DATA_BITS    8
#define  _9_DATA_BITS    9

/*************** # of stop bits ***************/
#define  ONE_STOP_BIT   1
#define  TWO_STOP_BIT   2

#endif /* UART_CONFIG_H_ */