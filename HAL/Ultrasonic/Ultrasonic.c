/*
 * Ultrasonic.c
 *
 * Created: 9/11/2022 9:15:02 PM
 *  Author: Khalil
 */ 
#include "Ultrasonic.h"

static volatile u16_t Ultrasonic_t1,Ultrasonic_t2,Ultrasonic_flag,OVF_Counter;

void ULTRASONIC_INIT(void)
{
	/****you can use timer in another mode except modes using ICR as top put take care dont reset timer****/
	TIMER1_INIT(TIMER1_NORMAL_MODE,TIMER1_SCALER_8,TIMER1_OC1A_DISCONNECTED,TIMER1_OC1B_DISCONNECTED);
	TIMER1_OV_SetCallBack(ISR_OVF_Func);
	TIMER1_ICU_SetCallBack(ISR_ICU_Func);
}

u8_t ULTRASONIC_GET_DISTANCE(ULTRASONIC_t ultrasonic_Trigger_pin)
{
	u8_t Local_u8Distance;
	u16_t Local_u16Time;
	//TCNT1_reg=0;
	OVF_Counter=0;
	Ultrasonic_flag=0;
	SET_BIT(TRIGGER_PORT,ultrasonic_Trigger_pin);
	_delay_us(10);
	CLEAR_BIT(TRIGGER_PORT,ultrasonic_Trigger_pin);
	TIMER1_ICU_TRIGGER_EDGE(RISING);
	TIMER1_OV_INT_Enable();
	TIMER1_ICU_INT_Enable();
	while(Ultrasonic_flag<2);
	Local_u16Time = Ultrasonic_t2 - Ultrasonic_t1 + ((u32_t)OVF_Counter*65535);
	Local_u8Distance = Local_u16Time/58;
	TIMER1_ICU_INT_Disable();
	return Local_u8Distance;
}

void ULTRASONIC_START(ULTRASONIC_t ultrasonic_Trigger_pin)
{
	if (Ultrasonic_flag==0)
	{
		SET_BIT(TRIGGER_PORT,ultrasonic_Trigger_pin);
		_delay_us(10);
		CLEAR_BIT(TRIGGER_PORT,ultrasonic_Trigger_pin);
		TIMER1_ICU_TRIGGER_EDGE(RISING);
		TIMER1_OV_INT_Enable();
		TIMER1_ICU_INT_Enable();
	}
}

u8_t ULTRASONIC_GET_DISTANCE2(u8_t* PtrDistance)
{
	u8_t Local_u8Distance;
	u16_t Local_u16Time;
	if (Ultrasonic_flag==2)
	{
		Local_u16Time = Ultrasonic_t2 - Ultrasonic_t1 + ((u32_t)OVF_Counter*65535);
		Local_u8Distance = Local_u16Time/58;
		*PtrDistance = Local_u8Distance;
		TIMER1_OV_INT_Enable();
		return 1;
	}
	return 0;
}


void ISR_OVF_Func(void)
{
	OVF_Counter++;
}

void ISR_ICU_Func()
{
	if (Ultrasonic_flag==0)
	{
		Ultrasonic_t1= ICR1_reg;
		Ultrasonic_flag=1;
		TIMER1_ICU_TRIGGER_EDGE(FAILLING);
	}
	else if (Ultrasonic_flag==1)
	{
		Ultrasonic_t2= ICR1_reg;
		Ultrasonic_flag=2;
		TIMER1_ICU_TRIGGER_EDGE(RISING);
		TIMER1_OV_INT_Disable();
		TIMER1_ICU_INT_Disable();
	}	
}