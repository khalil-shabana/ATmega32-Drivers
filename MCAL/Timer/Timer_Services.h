/*
 * Timer_Services.h
 *
 * Created: 9/7/2022 2:54:37 AM
 *  Author: Khalil
 */ 


#ifndef TIMER_SERVICES_H_
#define TIMER_SERVICES_H_

#include "Timer.h"

/************************************** PWM **************************************/

void Generate_PWM_ICR1_TOP(void);

void PWM_Freq_KHz(u16_t PWM_u16Freq);

void PWM_Freq_Hz(u16_t PWM_u16Freq);

void PWM_DutyCycle(u16_t PWM_u16Duty);

void PWM_Measuring(u32_t* PtrFreq, u8_t* PtrDuty);


// time must be <= 65536 
// if time > 65536 .. Change the prescaler
void SET_INT_TIME_ms(u16_t time, void (*LocalFPtr) (void));
void SET_INT_TIME_us(u16_t time, void (*LocalFPtr) (void));

#endif /* TIMER_SERVICES_H_ */