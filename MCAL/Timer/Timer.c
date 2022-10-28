/*
 * Timer.c
 *
 * Created: 8/16/2022 1:50:49 PM
 *  Author: Khalil
 */ 
#include "Timer.h"

/****************************Pointer to functions to be assigned to ISR*********************************/
static void (*TIMER0_OV_Fptr)  (void) =NULLPTR;
static void (*TIMER0_OC_Fptr)  (void) =NULLPTR;

static void (*TIMER1_OV_Fptr)  (void) =NULLPTR;
static void (*TIMER1_OCA_Fptr) (void) =NULLPTR;
static void (*TIMER1_OCB_Fptr) (void) =NULLPTR;
static void (*TIMER1_ICU_Fptr) (void) =NULLPTR;

/************************************************************************/
/*                             TIMER 0                                  */
/************************************************************************/

void TIMER0_INIT (TIMER0_MODE_t mode, TIMER0_SCALER_t scaler, TIMER0_OC_MODE_t OC_mode)
{
	switch (mode)
	{
		case TIMER0_NORMAL_MODE:
				CLEAR_BIT(TCCR0_reg,WGM00);
				CLEAR_BIT(TCCR0_reg,WGM01);
				break;
		case TIMER0_PHASE_CORRECT_MODE:
				SET_BIT(TCCR0_reg,WGM00);
				CLEAR_BIT(TCCR0_reg,WGM01);
				break;
		case TIMER0_CTC_MODE:
				 CLEAR_BIT(TCCR0_reg,WGM00);
				 SET_BIT(TCCR0_reg,WGM01);
				 break;
		case TIMER0_FAST_PWM_MODE:
				SET_BIT(TCCR0_reg,WGM00);
				SET_BIT(TCCR0_reg,WGM01);
				break;	
			
	}
	
	TCCR0_reg= TCCR0_reg & 0xf8; //1111 1000 (make sue the first 3 bits =0)
	TCCR0_reg= TCCR0_reg | scaler;
	
	switch (OC_mode)
	{
		case TIMER0_OC_DISCONNECTED:
			CLEAR_BIT(TCCR0_reg,COM00);
			CLEAR_BIT(TCCR0_reg,COM01);
			break;
		case TIMER0_OC_TOGGLE:
			SET_BIT(TCCR0_reg,COM00);
			CLEAR_BIT(TCCR0_reg,COM01);
			break;
		case TIMER0_OC_NON_INVERTING:
			CLEAR_BIT(TCCR0_reg,COM00);
			SET_BIT(TCCR0_reg,COM01);
			break;
		case TIMER0_OC_INVERTING:
			SET_BIT(TCCR0_reg,COM00);
			SET_BIT(TCCR0_reg,COM01);
			break;
		
	}
}

void TIMER0_OV_INT_Enable(void)
{
	SET_BIT(TIMSK_reg,TOIE0);
}

void TIMER0_OV_INT_Disable(void)
{
	CLEAR_BIT(TIMSK_reg,TOIE0);
}

void TIMER0_OC_INT_Enable(void)
{
	SET_BIT(TIMSK_reg,OCIE0);
}

void TIMER0_OC_INT_Disable(void)
{
	CLEAR_BIT(TIMSK_reg,OCIE0);
}

/*************************** TIMER0 Call-Back Functions ***************************/

void TIMER0_OV_SetCallBack(void(*Local_Fptr)(void))
{
	TIMER0_OV_Fptr=Local_Fptr;
}
void TIMER0_OC_SetCallBack(void(*Local_Fptr)(void))
{
	TIMER0_OC_Fptr=Local_Fptr;
}

/*************************** TIMER0 ISR Functions ***************************/
/*
ISR (TIMER0_OVF_vector)
{
	if (TIMER0_OV_Fptr != NULLPTR)
	{
		TIMER0_OV_Fptr();
	}
}*/

ISR (TIMER0_COMP_vector)
{
	if (TIMER0_OC_Fptr != NULLPTR)
	{
		TIMER0_OC_Fptr();
	}
}


/************************************************************************/
/*                             TIMER 1                                  */
/************************************************************************/

void TIMER1_INIT(TIMER1_MODE_t Timer1Mode,TIMER1_SCALER_t Timer1Scaler,  TIMER1_OC1A_MODE_t OC1A_Mode, TIMER1_OC1B_MODE_t OC1B_Mode)
{
	switch (Timer1Mode)
	{
		case TIMER1_NORMAL_MODE:
			CLEAR_BIT(TCCR1A_reg,WGM10);
			CLEAR_BIT(TCCR1A_reg,WGM11);
			CLEAR_BIT(TCCR1B_reg,WGM12);
			CLEAR_BIT(TCCR1B_reg,WGM13);
			break;
		
		case TIMER1_PHASE_CORRECT_8bit_0x00FF:
			SET_BIT(TCCR1A_reg,WGM10);
			CLEAR_BIT(TCCR1A_reg,WGM11);
			CLEAR_BIT(TCCR1B_reg,WGM12);
			CLEAR_BIT(TCCR1B_reg,WGM13);
			break;
		
		case TIMER1_PHASE_CORRECT_9bit_0x01FF:
			CLEAR_BIT(TCCR1A_reg,WGM10);
			SET_BIT(TCCR1A_reg,WGM11);
			CLEAR_BIT(TCCR1B_reg,WGM12);
			CLEAR_BIT(TCCR1B_reg,WGM13);
			break;
		
		case TIMER1_PHASE_CORRECT_10bit_0x03FF:
			SET_BIT(TCCR1A_reg,WGM10);
			SET_BIT(TCCR1A_reg,WGM11);
			CLEAR_BIT(TCCR1B_reg,WGM12);
			CLEAR_BIT(TCCR1B_reg,WGM13);
			break;
		
		case TIMER1_CTC_OCR1A_TOP_MODE:
			CLEAR_BIT(TCCR1A_reg,WGM10);
			CLEAR_BIT(TCCR1A_reg,WGM11);
			SET_BIT(TCCR1B_reg,WGM12);
			CLEAR_BIT(TCCR1B_reg,WGM13);
			break;
		
		case TIMER1_FAST_PWM_8bit_0x00FF:
			SET_BIT(TCCR1A_reg,WGM10);
			CLEAR_BIT(TCCR1A_reg,WGM11);
			SET_BIT(TCCR1B_reg,WGM12);
			CLEAR_BIT(TCCR1B_reg,WGM13);
			break;
		
		case TIMER1_FAST_PWM_9bit_0x01FF:
			CLEAR_BIT(TCCR1A_reg,WGM10);
			SET_BIT(TCCR1A_reg,WGM11);
			SET_BIT(TCCR1B_reg,WGM12);
			CLEAR_BIT(TCCR1B_reg,WGM13);
			break;
		
		case TIMER1_FAST_PWM_10bit_0x03FF:
			SET_BIT(TCCR1A_reg,WGM10);
			SET_BIT(TCCR1A_reg,WGM11);
			SET_BIT(TCCR1B_reg,WGM12);
			CLEAR_BIT(TCCR1B_reg,WGM13);
			break;
			
		case TIMER1_PHASE_FREQUENCY_Correct_ICR1_TOP_MODE:
			CLEAR_BIT(TCCR1A_reg,WGM10);
			CLEAR_BIT(TCCR1A_reg,WGM11);
			CLEAR_BIT(TCCR1B_reg,WGM12);
			SET_BIT(TCCR1B_reg,WGM13);
			break;
		
		case TIMER1_PHASE_FREQUENCY_Correct_OCR1A_TOP_MODE:
			SET_BIT(TCCR1A_reg,WGM10);
			CLEAR_BIT(TCCR1A_reg,WGM11);
			CLEAR_BIT(TCCR1B_reg,WGM12);
			SET_BIT(TCCR1B_reg,WGM13);
			break;
		
		case TIMER1_PHASE_CORRECT_ICR1_TOP_MODE:
			CLEAR_BIT(TCCR1A_reg,WGM10);
			SET_BIT(TCCR1A_reg,WGM11);
			CLEAR_BIT(TCCR1B_reg,WGM12);
			SET_BIT(TCCR1B_reg,WGM13);
			break;
		
		case TIMER1_PHASE_CORRECT_OCR1A_TOP_MODE:
			SET_BIT(TCCR1A_reg,WGM10);
			SET_BIT(TCCR1A_reg,WGM11);
			CLEAR_BIT(TCCR1B_reg,WGM12);
			SET_BIT(TCCR1B_reg,WGM13);
			break;
		
		case TIMER1_CTC_ICR1_TOP_MODE:
			CLEAR_BIT(TCCR1A_reg,WGM10);
			CLEAR_BIT(TCCR1A_reg,WGM11);
			SET_BIT(TCCR1B_reg,WGM12);
			SET_BIT(TCCR1B_reg,WGM13);
			break;
			
		case RESERVEDXXX:
			SET_BIT(TCCR1A_reg,WGM10);
			CLEAR_BIT(TCCR1A_reg,WGM11);
			SET_BIT(TCCR1B_reg,WGM12);
			SET_BIT(TCCR1B_reg,WGM13);
			break;
		
		case TIMER1_FAST_PWM_ICR1_TOP_MODE:
			CLEAR_BIT(TCCR1A_reg,WGM10);
			SET_BIT(TCCR1A_reg,WGM11);
			SET_BIT(TCCR1B_reg,WGM12);
			SET_BIT(TCCR1B_reg,WGM13);
			break;
		
		case TIMER1_FAST_PWM_OCR1A_TOP_MODE:
			SET_BIT(TCCR1A_reg,WGM10);
			SET_BIT(TCCR1A_reg,WGM11);
			SET_BIT(TCCR1B_reg,WGM12);
			SET_BIT(TCCR1B_reg,WGM13);
			break;
	}
	
	TCCR1B_reg &= 0xF8;
	TCCR1B_reg |= Timer1Scaler;
	
	switch (OC1A_Mode)
	{
		case TIMER1_OC1A_DISCONNECTED:
			CLEAR_BIT(TCCR1A_reg,COM1A0);
			CLEAR_BIT(TCCR1A_reg,COM1A1);
			break;
		
		case TIMER1_OC1A_TOGGLE:
			SET_BIT(TCCR1A_reg,COM1A0);
			CLEAR_BIT(TCCR1A_reg,COM1A1);
			
		case TIMER1_OC1A_NON_INVERTING:
			CLEAR_BIT(TCCR1A_reg,COM1A0);
			SET_BIT(TCCR1A_reg,COM1A1);
			break;
			
		case TIMER1_OC1A_INVERTING:
			SET_BIT(TCCR1A_reg,COM1A0);
			SET_BIT(TCCR1A_reg,COM1A1);
			break;
	}
	
	switch (OC1B_Mode)
	{
		case TIMER1_OC1B_DISCONNECTED:
		CLEAR_BIT(TCCR1B_reg,COM1B0);
		CLEAR_BIT(TCCR1B_reg,COM1B1);
		break;
		
		case TIMER1_OC1B_TOGGLE:
		SET_BIT(TCCR1A_reg,COM1B0);
		CLEAR_BIT(TCCR1A_reg,COM1B1);
		
		case TIMER1_OC1B_NON_INVERTING:
		CLEAR_BIT(TCCR1A_reg,COM1B0);
		SET_BIT(TCCR1A_reg,COM1B1);
		break;
		
		case TIMER1_OC1B_INVERTING:
		SET_BIT(TCCR1A_reg,COM1B0);
		SET_BIT(TCCR1A_reg,COM1B1);
		break;
	}
	 
}

void TIMER1_ICU_TRIGGER_EDGE(ICU_Trigger_Edge_t ICU_edge)
{
	if (ICU_edge == RISING)
	{
		SET_BIT(TCCR1B_reg,ICES1);
	}
	else if (ICU_edge == FAILLING)
	{
		CLEAR_BIT(TCCR1B_reg,ICES1);
	}
}

void TIMER1_OV_INT_Enable(void)
{
	SET_BIT(TIMSK_reg,TOIE1);
}

void TIMER1_OV_INT_Disable(void)
{
	CLEAR_BIT(TIMSK_reg,TOIE1);
}

void TIMER1_OCA_INT_Enable(void)
{
	SET_BIT(TIMSK_reg, OCIE1A);
}
void TIMER1_OCA_INT_Disable(void)
{
	CLEAR_BIT(TIMSK_reg, OCIE1A);
}

void TIMER1_OCB_INT_Enable(void)
{
	SET_BIT(TIMSK_reg, OCIE1B);
}
void TIMER1_OCB_INT_Disable(void)
{
	CLEAR_BIT(TIMSK_reg, OCIE1B);
}

void TIMER1_ICU_INT_Enable(void)
{
	SET_BIT(TIMSK_reg,TICIE1);
}

void TIMER1_ICU_INT_Disable(void)
{
	CLEAR_BIT(TIMSK_reg,TICIE1);
}

/*************************** TIMER1 Call-Back Functions ***************************/

void TIMER1_OV_SetCallBack(void(*Local_Fptr)(void))
{
	TIMER1_OV_Fptr=Local_Fptr;
}
void TIMER1_OCA_SetCallBack(void(*Local_Fptr)(void))
{
	TIMER1_OCA_Fptr=Local_Fptr;
}
void TIMER1_OCB_SetCallBack(void(*Local_Fptr)(void))
{
	TIMER1_OCB_Fptr=Local_Fptr;
}
void TIMER1_ICU_SetCallBack(void(*Local_Fptr)(void))
{
	TIMER1_ICU_Fptr=Local_Fptr;
}

/*************************** TIMER1 ISR Functions ***************************/

ISR (TIMER1_OVF_vector)
{
	if (TIMER1_OV_Fptr != NULLPTR)
	{
		TIMER1_OV_Fptr();
	}
}

ISR (TIMER1_COMPA_vector)
{
	if (TIMER1_OCA_Fptr != NULLPTR)
	{
		TIMER1_OCA_Fptr();
	}
}

ISR (TIMER1_COMPB_vector)
{
	if (TIMER1_OCB_Fptr != NULLPTR)
	{
		TIMER1_OCB_Fptr();
	}
}

ISR (TIMER1_CAPT_vector)
{
	if (TIMER1_ICU_Fptr != NULLPTR)
	{
		TIMER1_ICU_Fptr();
	}
}
