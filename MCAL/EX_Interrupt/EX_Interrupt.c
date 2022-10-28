/*
 * EX_Interrupt.c
 *
 * Created: 8/10/2022 3:36:29 PM
 *  Author: Khalil
 */ 
#include "EX_Interrupt.h"
#include "LCD.h"

/*******************Pointer to function to be assigned to ISR*******************/

static void (*INT0_FuncPtr)(void) = NULLPTR;
static void (*INT1_FuncPtr)(void) = NULLPTR;
static void (*INT2_FuncPtr)(void) = NULLPTR;

/******************* call back functions *******************/
void EX_INT_Set_Call_Back(EX_INT_Source_t INT_Source, void (*Local_ptr)(void))
{
	switch (INT_Source)
	{
		case EX_INT0:
			INT0_FuncPtr= Local_ptr;
			break;
		 case EX_INT1:
			 INT1_FuncPtr= Local_ptr;
			 break;
		 case EX_INT2:
			INT2_FuncPtr= Local_ptr;
			break;
	}
}


void EX_INT_Enable(EX_INT_Source_t INT_Source)
{
	switch(INT_Source)
	{
		case EX_INT0:
			SET_BIT(GICR_reg,INT0);
			break;
		
		case EX_INT1:
			SET_BIT(GICR_reg,INT1);
			break;
		
		case EX_INT2:
			SET_BIT(GICR_reg,INT2);
			break;
	}
}

void EX_INT_Disable(EX_INT_Source_t INT_Source)
{
	switch(INT_Source)
	{
		case EX_INT0:
			CLEAR_BIT(GICR_reg,INT0);
			break;
		
		case EX_INT1:
			CLEAR_BIT(GICR_reg,INT1);
			break;
		
		case EX_INT2:
			CLEAR_BIT(GICR_reg,INT2);
			break;
	}
}


void EX_INT_TriggerEdge(EX_INT_Source_t INT_Source, EX_INT_TriggerEdge_t Edge)
{
	switch (INT_Source)
	{
		case EX_INT0:
			switch (Edge)
			{
				case LOW_LEVEL:
					CLEAR_BIT(MCUCR_reg,ISC00);
					CLEAR_BIT(MCUCR_reg,ISC01);
					break;
				
				case ANY_LOGIC_CHANGE:
					SET_BIT(MCUCR_reg,ISC00);
					CLEAR_BIT(MCUCR_reg,ISC01);
					break;
					
				case FALLING_EDGE:
					CLEAR_BIT(MCUCR_reg,ISC00);
					SET_BIT(MCUCR_reg,ISC01);
					break;
				
				case RISING_EDGE:
					SET_BIT(MCUCR_reg,ISC00);
					SET_BIT(MCUCR_reg,ISC01);
					break;										
			}
			break;
		
		case EX_INT1:
			switch (Edge)
			{
				case LOW_LEVEL:
					CLEAR_BIT(MCUCR_reg,ISC10);
					CLEAR_BIT(MCUCR_reg,ISC11);
					break;
				
				case ANY_LOGIC_CHANGE:
					SET_BIT(MCUCR_reg,ISC10);
					CLEAR_BIT(MCUCR_reg,ISC11);
					break;
				
				case FALLING_EDGE:
					CLEAR_BIT(MCUCR_reg,ISC10);
					SET_BIT(MCUCR_reg,ISC11);
					break;
				
				case RISING_EDGE:
					SET_BIT(MCUCR_reg,ISC10);
					SET_BIT(MCUCR_reg,ISC11);
					break;
			}
			break;
			
		case EX_INT2:
			switch (Edge)
			{				
				case FALLING_EDGE:
					CLEAR_BIT(MCUCSR_reg,ISC2);
					break;
				
				case RISING_EDGE:
					SET_BIT(MCUCSR_reg,ISC2);
					break;
				
				default:
					CLEAR_BIT(MCUCSR_reg,ISC2); //default: Falling edge
			}
			break;
	}
		
}

/******************* ISR *******************/
ISR (INT0_vector)
{	
	if (INT0_FuncPtr != NULLPTR)
	{
		INT0_FuncPtr();
	}
}

ISR (INT1_vector)
{
	if (INT1_FuncPtr != NULLPTR)
	{
		INT1_FuncPtr();
	}
}

ISR (INT2_vector)
{
	if (INT2_FuncPtr != NULLPTR)
	{
		INT2_FuncPtr();
	}
}
