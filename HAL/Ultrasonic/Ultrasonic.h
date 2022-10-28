/*
 * Ultrasonic.h
 *
 * Created: 9/11/2022 9:14:53 PM
 *  Author: Khalil
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <util/delay.h>
#include "IO_ATMEGA32.h"
#include "Timer.h"

/******************* ‘‘ USER configuration ’’ *******************/

#define TRIGGER_PORT	PORTD_reg

typedef enum{
	
	ULTRASONIC_1 = PIN_0,
	ULTRASONIC_2 = PIN_1,
	ULTRASONIC_3 = PIN_2,
	ULTRASONIC_4 = PIN_3	
}ULTRASONIC_t;

void ULTRASONIC_INIT(void);

u8_t ULTRASONIC_GET_DISTANCE(ULTRASONIC_t ultrasonic_Trigger_pin);

void ULTRASONIC_START(ULTRASONIC_t ultrasonic_Trigger_pin);
u8_t ULTRASONIC_GET_DISTANCE2(u8_t* PtrDistance);

void ISR_OVF_Func();
void ISR_ICU_Func();

#endif /* ULTRASONIC_H_ */