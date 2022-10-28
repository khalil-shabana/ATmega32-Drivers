/*
 * IO_ATMEGA32.h
 *
 *  Created on: Jul 26, 2022
 *      Author: Khalil
 */
#include "ATmega32_Registers.h"
#include "Data_types.h"
#include "Bit_Mask.h"
#include "IO_config.h"
#include "IO_private.h"


#ifndef REPO_MCAL_DIO_IO_ATMEGA32_H_
#define REPO_MCAL_DIO_IO_ATMEGA32_H_


#define u8_Direction_input 0x00
#define u8_Direction_output 0xFF

typedef enum{
	INPUT = 0,
	OUTPUT= 1
}IO_direction_t;
typedef enum {
	PIN_0 = 0,
	PIN_1 = 1,
	PIN_2 = 2,
	PIN_3 = 3,
	PIN_4 = 4,
	PIN_5 = 5,
	PIN_6 = 6,
	PIN_7 = 7
}IO_pin_number_t;

typedef enum{
	LOW = 0,
	HIGH= 1
}IO_PinVal_t;

typedef enum{
	GROUP_A = 1,
	GROUP_B = 2,
	GROUP_C = 3,
	GROUP_D = 4
}IO_PORT_t;

void IO_Init(void);

// ===================PIN==========================
// DATA
/* Get pin value */
IO_PinVal_t IO_GetPinVal (IO_PORT_t port_name, IO_pin_number_t pin_Num);  

/* Write pin value */
void IO_WritePinVal (IO_PORT_t port_name, IO_pin_number_t pin_Num, IO_PinVal_t pin_val);

// DIRECTION
/* Read pin direction */
IO_direction_t IO_GetPinDir (IO_PORT_t port_name, IO_pin_number_t pin_Num);

/* Write pin direction */
void IO_WritePinDir (IO_PORT_t port_name, IO_pin_number_t pin_Num, IO_direction_t pin_dir);

// ===================PORT==========================
// DATA
/* Read port value */
u8_t IO_GetPortVal (IO_PORT_t port_name);

/* Write port value */
void IO_WritePortVal (IO_PORT_t port_name, u8_t port_val);

// DIRECTION
/* Read port direction */
IO_direction_t IO_GetPortDir (IO_PORT_t port_name);
/* Write port direction */
void IO_WritePortDir (IO_PORT_t port_name, IO_direction_t port_dir);


#endif /* REPO_MCAL_DIO_IO_ATMEGA32_H_ */
