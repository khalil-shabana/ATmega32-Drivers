/*
 * Timer_Services.c
 *
 * Created: 9/7/2022 2:54:27 AM
 *  Author: Khalil
 */ 
#include "Timer_Services.h"

volatile u16_t u16_t1,u16_t2,u16_t3,TIMER_Service_flag=0;
static void ICU_Func (void);
/************************************** PWM **************************************/

void Generate_PWM_ICR1_TOP(void)
{
	TIMER1_INIT(TIMER1_FAST_PWM_ICR1_TOP_MODE,TIMER1_SCALER_8,TIMER1_OC1A_NON_INVERTING,TIMER1_OC1B_DISCONNECTED);
}

void PWM_Freq_KHz(u16_t PWM_u16Freq)
{
	if (PWM_u16Freq == 0);
	else
	{
		u16_t T_total = (1/PWM_u16Freq)*1000;
		if(T_total >= 1)
		{
			ICR1_reg= T_total -1;
		}
		else ICR1_reg =0;
	}
}

void PWM_Freq_Hz(u16_t PWM_u16Freq)
{
	if (PWM_u16Freq == 0);
	else
	{
		u16_t T_Total = (1/PWM_u16Freq)*(u32_t)1000000;
		if(T_Total >= 1)
		{
			ICR1_reg= T_Total -1;
		}
		else ICR1_reg =0;
	}
}

void PWM_DutyCycle(u16_t PWM_u16Duty)
{
	if (PWM_u16Duty <= 100)
	{
		u16_t T_ON = ((u32_t)PWM_u16Duty*(ICR1_reg+1))/100;
		
		if (T_ON >1)
		{
			OCR1A_reg= T_ON -1;
		}
		else OCR1A_reg= 0;
	}
}

void PWM_Measuring(u32_t* PtrFreq, u8_t* PtrDuty)
{
	u16_t T_on,T_off;
	TCNT1_reg =0;
	
	TIMER1_ICU_SetCallBack(ICU_Func);
	TIMER1_ICU_TRIGGER_EDGE(RISING);
	TIMER1_ICU_INT_Enable();
	TIMER_Service_flag =0;
	while(TIMER_Service_flag<3);
	 // it must wait to make sure that the interrupts happened,
	 // so it's a sync. function
	T_on =u16_t2 - u16_t1;
	T_off=u16_t3 - u16_t2;
	
	*PtrDuty = ((u32_t)T_on*100) / ((u32_t)T_on+T_off);
	*PtrFreq = (u32_t)1000000/ ((u32_t)T_off+T_on);
}

static void ICU_Func (void)
{
	if (TIMER_Service_flag==0 )
	{
		u16_t1= ICR1_reg;
		TIMER1_ICU_TRIGGER_EDGE(FAILLING);
		TIMER_Service_flag =1;
	}
	else if (TIMER_Service_flag ==1)
	{
		u16_t2 =ICR1_reg;
		TIMER1_ICU_TRIGGER_EDGE(RISING);
		TIMER_Service_flag=2;
	}
	else if (TIMER_Service_flag==2)
	{
		u16_t3=ICR1_reg;
		TIMER1_ICU_INT_Disable();
		TIMER_Service_flag=3; 
	}
}

//----------- Set time for an interrupt -------------

void SET_INT_TIME_ms(u16_t time, void (*LocalFPtr) (void))
{
	TIMER1_INIT(TIMER1_CTC_OCR1A_TOP_MODE,TIMER1_SCALER_8,TIMER1_OC1A_DISCONNECTED,TIMER1_OC1B_DISCONNECTED);
	OCR1A_reg = (time*1000) - 1;
	TIMER1_OCA_SetCallBack(LocalFPtr);
	TIMER1_OCA_INT_Enable();
}

void SET_INT_TIME_us(u16_t time, void (*LocalFPtr) (void))
{
	TIMER1_INIT(TIMER1_CTC_OCR1A_TOP_MODE,TIMER1_SCALER_8,TIMER1_OC1A_DISCONNECTED,TIMER1_OC1B_DISCONNECTED);
	OCR1A_reg = time - 1;
	TIMER1_OCA_SetCallBack(LocalFPtr);
	TIMER1_OCA_INT_Enable();
}