/*
 * ADC.h
 *
 * Created: 8/30/2022 6:16:05 PM
 *  Author: Khalil
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "ATmega32_Registers.h"
#include "Data_types.h"
#include "Bit_Mask.h"
#include "ADC_config.h"

typedef enum{
	ADC_Channel0 =0,
	ADC_Channel1,
	ADC_Channel2,
	ADC_Channel3,
	ADC_Channel4,
	ADC_Channel5,
	ADC_Channel6,
	ADC_Channel7
}ADC_Channel_t;

/*
typedef enum{
	ADC_VOLTAGE_REF_AREF,
	ADC_VOLTAGE_REF_AVCC,
	ADC_VOLTAGE_REF_2_56
}ADC_Voltage_Ref_t;*/

/*
typedef enum{
	ADC_SCALE_2   =1,
	ADC_SCALE_4   =2,
	ADC_SCALE_8   =3,
	ADC_SCALE_16  =4,
	ADC_SCALE_32  =5,
	ADC_SCALE_64  =6,
	ADC_SCALE_128 =7
}ADC_Prescaler_t;*/

typedef enum{
	 AUTO_TRIG_SRC_FREE_RUNNING_MODE =0,
	 AUTO_TRIG_SRC_Analog_Comparator =1,
	 AUTO_TRIG_SRC_External_Interrupt_Request0,
	 AUTO_TRIG_SRC_Timer0_Compare_Match,
	 AUTO_TRIG_SRC_Timer0_Overflow,
	 AUTO_TRIG_SRC_Timer1_Compare_MatchB,
	 AUTO_TRIG_SRC_Timer1_Overflow,
	 AUTO_TRIG_SRC_Timer1_Capture_Event 
}ADC_AUTO_TRIG_SRC_t;

#define ADC_converted_data	*((volatile u16_t*) 0x24) //used to receive the result ADCL and ADCH 
		
void ADC_INIT(void);
void ADC_START_CON(ADC_Channel_t ADC_Local_Ch);

void ADC_AUTO_TRIGGER_Enable(ADC_AUTO_TRIG_SRC_t ADC_Local_Auto_TRIG_SRC);
void ADC_AUTO_TRIGGER_Disable(void); //Single conversion mode

void ADC_INTERRUPT_ENABLE(void);
void ADC_INTERRUPT_DISABLE();
void ADC_SET_CALL_BACK(void (*Local_ptr)(void));

u16_t ADC_GET_RESULT(void);



#endif /* ADC_H_ */