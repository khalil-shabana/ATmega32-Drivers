/*
 * EX_Interrupt.h
 *
 * Created: 8/10/2022 3:36:46 PM
 *  Author: Khalil
 */ 


#ifndef EX_INTERRUPT_H_
#define EX_INTERRUPT_H_

#include "Data_types.h"
#include "Bit_Mask.h"
#include "ATmega32_Registers.h"

typedef enum {
	EX_INT0= 0,
	EX_INT1,
	EX_INT2
}EX_INT_Source_t;

typedef enum {
	LOW_LEVEL= 0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE,
}EX_INT_TriggerEdge_t;

//initialization

//enable
void EX_INT_Enable(EX_INT_Source_t INT_Source);

void EX_INT_Disable(EX_INT_Source_t INT_Source);

void EX_INT_TriggerEdge(EX_INT_Source_t INT_Source, EX_INT_TriggerEdge_t Edge);

void EX_INT_Set_Call_Back(EX_INT_Source_t INT_Source, void (*Local_ptr)(void));

#endif /* EX_INTERRUPT_H_ */