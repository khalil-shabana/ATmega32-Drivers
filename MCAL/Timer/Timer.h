/*
 * Timer.h
 *
 * Created: 8/16/2022 1:51:02 PM
 *  Author: Khalil
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "Data_types.h"
#include "ATmega32_Registers.h"
#include "Bit_Mask.h"


/************************************************************************/
/*                             TIMER 0                                  */
/************************************************************************/


typedef enum {
	TIMER0_NORMAL_MODE= 0, 
	TIMER0_PHASE_CORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FAST_PWM_MODE
}TIMER0_MODE_t;

typedef enum {
	TIMER0_STOP= 0,
	TIMER0_SCALER_1,
	TIMER0_SCALER_8,
	TIMER0_SCALER_64,
	TIMER0_SCALER_256,
	TIMER0_SCALER_1024,
				/*using external freq. from external oscillator*/
	EXTERNAL_FAILING, //External clock source on T0 pin. Clock on falling edge
	EXTERNAL_RISING	  // External clock source on T0 pin. Clock on rising edge.
}TIMER0_SCALER_t;

typedef enum{
	TIMER0_OC_DISCONNECTED= 0,
	TIMER0_OC_TOGGLE,
	TIMER0_OC_NON_INVERTING,
	TIMER0_OC_INVERTING
}TIMER0_OC_MODE_t;
	
void TIMER0_INIT (TIMER0_MODE_t mode, TIMER0_SCALER_t scaler, TIMER0_OC_MODE_t OC_mode);
void TIMER0_OV_INT_Enable(void);
void TIMER0_OV_INT_Disable(void);
void TIMER0_OC_INT_Enable(void);
void TIMER0_OC_INT_Disable(void);
void TIMER0_OV_SetCallBack(void(*Local_Fptr)(void));
void TIMER0_OC_SetCallBack(void(*Local_Fptr)(void));

/************************************************************************/
/*                             TIMER 1                                  */
/************************************************************************/

typedef enum {
	TIMER1_NORMAL_MODE= 0,		//TOP=0xFFFF
	TIMER1_PHASE_CORRECT_8bit_0x00FF,
	TIMER1_PHASE_CORRECT_9bit_0x01FF,
	TIMER1_PHASE_CORRECT_10bit_0x03FF,
	TIMER1_CTC_OCR1A_TOP_MODE,
	TIMER1_FAST_PWM_8bit_0x00FF,
	TIMER1_FAST_PWM_9bit_0x01FF,
	TIMER1_FAST_PWM_10bit_0x03FF,
	TIMER1_PHASE_FREQUENCY_Correct_ICR1_TOP_MODE,
	TIMER1_PHASE_FREQUENCY_Correct_OCR1A_TOP_MODE,
	TIMER1_PHASE_CORRECT_ICR1_TOP_MODE,
	TIMER1_PHASE_CORRECT_OCR1A_TOP_MODE,
	TIMER1_CTC_ICR1_TOP_MODE,
	RESERVEDXXX,
	TIMER1_FAST_PWM_ICR1_TOP_MODE,
	TIMER1_FAST_PWM_OCR1A_TOP_MODE,
}TIMER1_MODE_t;

typedef enum{
	TIMER1_STOP=0,
	TIMER1_SCALER_1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
	EXTERNAL0_FALLING,
	EXTERNAL0_RISING
}TIMER1_SCALER_t;

typedef enum{
	TIMER1_OC1A_DISCONNECTED= 0,	// Normal port operation
	TIMER1_OC1A_TOGGLE,				
	TIMER1_OC1A_NON_INVERTING,		
	TIMER1_OC1A_INVERTING			
}TIMER1_OC1A_MODE_t;

typedef enum{
	TIMER1_OC1B_DISCONNECTED= 0,	
	TIMER1_OC1B_TOGGLE,
	TIMER1_OC1B_NON_INVERTING,
	TIMER1_OC1B_INVERTING
}TIMER1_OC1B_MODE_t;

typedef enum{
	RISING,
	FAILLING
}ICU_Trigger_Edge_t;

void TIMER1_INIT(TIMER1_MODE_t Timer1Mode,TIMER1_SCALER_t Timer1Scaler,  TIMER1_OC1A_MODE_t OC1A_Mode, TIMER1_OC1B_MODE_t OC1B_Mode);

void TIMER1_OV_INT_Enable(void);
void TIMER1_OV_INT_Disable(void);

void TIMER1_OCA_INT_Enable(void);
void TIMER1_OCA_INT_Disable(void);

void TIMER1_OCB_INT_Enable(void);
void TIMER1_OCB_INT_Disable(void);

void TIMER1_ICU_TRIGGER_EDGE(ICU_Trigger_Edge_t edge);
void TIMER1_ICU_INT_Enable(void);
void TIMER1_ICU_INT_Disable(void);

void TIMER1_OV_SetCallBack(void(*Local_Fptr)(void));
void TIMER1_OCA_SetCallBack(void(*Local_Fptr)(void));
void TIMER1_OCB_SetCallBack(void(*Local_Fptr)(void));
void TIMER1_ICU_SetCallBack(void(*Local_Fptr)(void));

#endif /* TIMER_H_ */