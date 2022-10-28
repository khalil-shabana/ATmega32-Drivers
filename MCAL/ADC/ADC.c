/*
 * ADC.c
 *
 * Created: 8/30/2022 6:16:15 PM
 *  Author: Khalil
 */ 

#include "ADC.h"

/*******************Pointer to function to be assigned to ISR*******************/

static void (*ADC_FuncPtr)(void) = NULLPTR;

void ADC_INIT(void)
{
	/******************* Selecting voltage reference *******************/
	
	#ifdef  ADC_VOLTAGE_REF_AREF
	CLEAR_BIT(ADMUX_reg,REFS0);
	CLEAR_BIT(ADMUX_reg,REFS1);
	#endif
	
	#ifdef ADC_VOLTAGE_REF_AVCC
	SET_BIT(ADMUX_reg,REFS0);
	CLEAR_BIT(ADMUX_reg,REFS1);
	#endif
	
	#ifdef ADC_VOLTAGE_REF_2_56V
	SET_BIT(ADMUX_reg,REFS0);
	SET_BIT(ADMUX_reg,REFS1);
	#endif
	
	/********************** Selecting ADC Mode **********************/
	
	#ifdef SINGLE_CON_MODE
	CLEAR_BIT(ADCSRA_reg,ADATE);
	#endif
	
	#ifdef FREE_RUNNING_MODE
	SET_BIT(ADCSRA_reg,ADATE);
	CLEAR_BIT(SFIOR_reg,ADTS0);
	CLEAR_BIT(SFIOR_reg,ADTS1);
	CLEAR_BIT(SFIOR_reg,ADTS2);
	#endif
	
	/********************** Selecting ADC Scale **********************/
	#ifdef ADC_SCALE_2
	SET_BIT(ADCSRA_reg,ADPS0);
	CLEAR_BIT(ADCSRA_reg,ADPS1);
	CLEAR_BIT(ADCSRA_reg,ADPS2);
	#endif
	
	#ifdef ADC_SCALE_4
	CLEAR_BIT(ADCSRA_reg,ADPS0);
	SET_BIT(ADCSRA_reg,ADPS1);
	CLEAR_BIT(ADCSRA_reg,ADPS2);
	#endif
	
	#ifdef ADC_SCALE_8
	SET_BIT(ADCSRA_reg,ADPS0);
	SET_BIT(ADCSRA_reg,ADPS1);
	CLEAR_BIT(ADCSRA_reg,ADPS2);
	#endif
	
	#ifdef ADC_SCALE_16
	CLEAR_BIT(ADCSRA_reg,ADPS0);
	CLEAR_BIT(ADCSRA_reg,ADPS1);
	SET_BIT(ADCSRA_reg,ADPS2);
	#endif
	
	#ifdef ADC_SCALE_32
	SET_BIT(ADCSRA_reg,ADPS0);
	CLEAR_BIT(ADCSRA_reg,ADPS1);
	SET_BIT(ADCSRA_reg,ADPS2);
	#endif
	
	#ifdef ADC_SCALE_64
	CLEAR_BIT(ADCSRA_reg,ADPS0);
	SET_BIT(ADCSRA_reg,ADPS1);
	SET_BIT(ADCSRA_reg,ADPS2);
	#endif
	
	#ifdef ADC_SCALE_128
	SET_BIT(ADCSRA_reg,ADPS0);
	SET_BIT(ADCSRA_reg,ADPS1);
	SET_BIT(ADCSRA_reg,ADPS2);
	#endif
	
	/********************** Selecting Adjustment **********************/
	#ifdef ADC_LEFT_ADJUST
	SET_BIT(ADMUX_reg,ADLAR);
	#endif
	
	#ifdef ADC_RIGHT_ADJUST
	CLEAR_BIT(ADMUX_reg,ADLAR);
	#endif
	/********************** Clearing Interrupt flag **********************/
	SET_BIT(ADCSRA_reg,ADIF);
	/********************** Enabling ADC **********************/
	SET_BIT(ADCSRA_reg,ADEN);
	
}

void ADC_START_CON(ADC_Channel_t Local_Channel)
{
	ADMUX_reg &= 0xE0; //1110 0000; to make sure that Channel Selection Bits = zero
	ADMUX_reg |= Local_Channel;
	SET_BIT(ADCSRA_reg,ADSC);
}

void ADC_AUTO_TRIGGER_Enable(ADC_AUTO_TRIG_SRC_t ADC_Local_Auto_TRIG_SRC)
{
	SET_BIT(ADCSRA_reg,ADATE);		   //Auto trigger enable
	CLEAR_BIT(SFIOR_reg,Reserved_Bit); //this bit must be written zero when SFIOR is written
	
	switch(ADC_Local_Auto_TRIG_SRC)
	{
		case AUTO_TRIG_SRC_FREE_RUNNING_MODE:
				CLEAR_BIT(SFIOR_reg,ADTS0);
				CLEAR_BIT(SFIOR_reg,ADTS1);
				CLEAR_BIT(SFIOR_reg,ADTS2);
				
		case AUTO_TRIG_SRC_Analog_Comparator:
				SET_BIT(SFIOR_reg,ADTS0);
				CLEAR_BIT(SFIOR_reg,ADTS1);
				CLEAR_BIT(SFIOR_reg,ADTS2);
				
		case AUTO_TRIG_SRC_External_Interrupt_Request0:
				CLEAR_BIT(SFIOR_reg,ADTS0);
				SET_BIT(SFIOR_reg,ADTS1);
				CLEAR_BIT(SFIOR_reg,ADTS2);
		
		case AUTO_TRIG_SRC_Timer0_Compare_Match:
				SET_BIT(SFIOR_reg,ADTS0);
				SET_BIT(SFIOR_reg,ADTS1);
				CLEAR_BIT(SFIOR_reg,ADTS2);
				
		case AUTO_TRIG_SRC_Timer0_Overflow:
				CLEAR_BIT(SFIOR_reg,ADTS0);
				CLEAR_BIT(SFIOR_reg,ADTS1);
				SET_BIT(SFIOR_reg,ADTS2);
				
		case AUTO_TRIG_SRC_Timer1_Compare_MatchB:
				SET_BIT(SFIOR_reg,ADTS0);
				CLEAR_BIT(SFIOR_reg,ADTS1);
				SET_BIT(SFIOR_reg,ADTS2);
				
		case AUTO_TRIG_SRC_Timer1_Overflow:
				CLEAR_BIT(SFIOR_reg,ADTS0);
				SET_BIT(SFIOR_reg,ADTS1);
				SET_BIT(SFIOR_reg,ADTS2);
				
		case AUTO_TRIG_SRC_Timer1_Capture_Event:
				SET_BIT(SFIOR_reg,ADTS0);
				SET_BIT(SFIOR_reg,ADTS1);
				SET_BIT(SFIOR_reg,ADTS2);
	}
}

void ADC_AUTO_TRIGGER_Disable(void)
{
	CLEAR_BIT(ADCSRA_reg,ADATE); //Disable (ADC in single conversion mode)
}

void ADC_INTERRUPT_ENABLE(void)
{
	SET_BIT(ADCSRA_reg,ADIE);
}
void ADC_INTERRUPT_DISABLE()
{
	CLEAR_BIT(ADCSRA_reg,ADIE);
}
void ADC_SET_CALL_BACK(void (*Local_ptr)(void))
{
	ADC_FuncPtr =Local_ptr;
}

u16_t ADC_GET_RESULT(void)
{
	if (GET_BIT(ADCSRA_reg,ADATE))
	{
		return ADC_converted_data;
	}
	else
	{
		while(GET_BIT(ADCSRA_reg,ADSC)); //cleared by hardware after conversion complete
		return ADC_converted_data;
	}
}


ISR (ADC_vector)
{
	if (ADC_FuncPtr != NULLPTR)
	{
		ADC_FuncPtr();
	}
}