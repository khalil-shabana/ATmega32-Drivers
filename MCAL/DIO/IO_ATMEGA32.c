/*
 * IO_ATMEGA32.c
 *
 *  Created on: Jul 26, 2022
 *      Author: Khalil
 */

#include "IO_ATMEGA32.h"

void IO_Init(void)
{
	DDRA_reg = PORTA_DIR;
	DDRB_reg = PORTB_DIR;
	DDRC_reg = PORTC_DIR;
	DDRD_reg = PORTD_DIR;

	PORTA_reg = PORTA_INIT;
	PORTB_reg = PORTB_INIT;
	PORTC_reg = PORTC_INIT;
	PORTD_reg = PORTD_INIT;
}
// ===================PIN==========================
// DATA
/* Get pin value */
IO_PinVal_t IO_GetPinVal (IO_PORT_t port_name, IO_pin_number_t pin_Num)
{
	IO_PinVal_t pin_value = LOW;	//initial value
	switch(port_name)
	{
		case GROUP_A:
			pin_value = GET_BIT(PINA_reg, pin_Num);
			break;

		case GROUP_B:
			pin_value = GET_BIT(PINB_reg, pin_Num);
			break;

		case GROUP_C:
			pin_value = GET_BIT(PINC_reg, pin_Num);
			break;

		case GROUP_D:
			pin_value = GET_BIT(PIND_reg, pin_Num);
			break;

		default:{}
	}
	return pin_value;
}

 /* Write pin value */
void IO_WritePinVal (IO_PORT_t port_name, IO_pin_number_t pin_Num, IO_PinVal_t pin_val)
{
		switch(port_name)
	{
		case GROUP_A:
			(pin_val)? SET_BIT(PORTA_reg, pin_Num):CLEAR_BIT(PORTA_reg, pin_Num);
			break;

		case GROUP_B:
			(pin_val)? SET_BIT(PORTB_reg, pin_Num):CLEAR_BIT(PORTB_reg, pin_Num);
			break;

		case GROUP_C:
			(pin_val)? SET_BIT(PORTC_reg, pin_Num):CLEAR_BIT(PORTC_reg, pin_Num);
			break;

		case GROUP_D:
			(pin_val)? SET_BIT(PORTD_reg, pin_Num):CLEAR_BIT(PORTD_reg, pin_Num);
			break;

		default:{}
	}
}

// DIRECTION
/* Read pin direction */
IO_direction_t IO_GetPinDir (IO_PORT_t port_name, IO_pin_number_t pin_Num)
{
	IO_direction_t pin_dir = INPUT;		//initial value
	switch(port_name)
	{
		case GROUP_A:
			pin_dir = GET_BIT(DDRA_reg, pin_Num);
			break;

		case GROUP_B:
			pin_dir = GET_BIT(DDRB_reg, pin_Num);
			break;

		case GROUP_C:
			pin_dir = GET_BIT(DDRC_reg, pin_Num);
			break;

		case GROUP_D:
			pin_dir = GET_BIT(DDRD_reg, pin_Num);
			break;

		default:{}
	}
	return pin_dir;
}

/* Write pin direction */
void IO_WritePinDir (IO_PORT_t port_name, IO_pin_number_t pin_Num, IO_direction_t pin_dir)
{
	switch(port_name)
	{
		case GROUP_A:
			(pin_dir)? SET_BIT(DDRA_reg, pin_Num):CLEAR_BIT(DDRA_reg, pin_Num);
			break;

		case GROUP_B:
			(pin_dir)? SET_BIT(DDRB_reg, pin_Num):CLEAR_BIT(DDRB_reg, pin_Num);
			break;

		case GROUP_C:
			(pin_dir)? SET_BIT(DDRC_reg, pin_Num):CLEAR_BIT(DDRC_reg, pin_Num);
			break;

		case GROUP_D:
			(pin_dir)? SET_BIT(DDRD_reg, pin_Num):CLEAR_BIT(DDRD_reg, pin_Num);
			break;

		default:{}
	}
}

//===================PORT==========================
// DATA
/* Read port value */
u8_t IO_GetPortVal (IO_PORT_t port_name)
{
	u8_t port_val = 0x00; //initial value
	switch(port_name)
	{
		case GROUP_A:
			port_val = PINA_reg;
			break;

		case GROUP_B:
			port_val = PINB_reg;
			break;

		case GROUP_C:
			port_val = PINC_reg;
			break;

		case GROUP_D:
			port_val = PIND_reg;
			break;

		default:{}
	}
	return port_val;
}

/* Write port value */
void IO_WritePortVal (IO_PORT_t port_name, u8_t port_val)
{
	switch(port_name)
	{
		case GROUP_A:
			PORTA_reg = port_val;
			break;

		case GROUP_B:
			PORTB_reg = port_val;
			break;

		case GROUP_C:
			PORTC_reg = port_val;
			break;

		case GROUP_D:
			PORTD_reg = port_val;
			break;

		default:{}
	}
}

// DIRECTION
/* Read port direction */
IO_direction_t IO_GetPortDir (IO_PORT_t port_name)
{
	u8_t port_dir = u8_Direction_input;	  //initial value
	switch(port_name)
	{
		case GROUP_A:
			port_dir = DDRA_reg;
			break;

		case GROUP_B:
			port_dir = DDRB_reg;
			break;

		case GROUP_C:
			port_dir = DDRC_reg;
			break;

		case GROUP_D:
			port_dir = DDRD_reg;
			break;

		default:{}
	}
	return port_dir;
}

/* Write port direction */
void IO_WritePortDir (IO_PORT_t port_name, IO_direction_t port_dir)
{
	switch(port_name)
	{
		case GROUP_A:
			(port_dir)? (DDRA_reg = u8_Direction_output) : (DDRA_reg = u8_Direction_input);
			break;

		case GROUP_B:
			(port_dir)? (DDRB_reg = u8_Direction_output) : (DDRB_reg = u8_Direction_input);
			break;

		case GROUP_C:
			(port_dir)? (DDRC_reg = u8_Direction_output) : (DDRC_reg = u8_Direction_input);
			break;

		case GROUP_D:
			(port_dir)? (DDRD_reg = u8_Direction_output) : (DDRD_reg = u8_Direction_input);
			break;

		default:{}
	}
}
