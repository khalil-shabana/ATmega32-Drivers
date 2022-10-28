/*
 * ADC_config.h
 *
 * Created: 9/2/2022 2:44:24 AM
 *  Author: Khalil
 */ 


#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_


/* Voltage reference options : 
 * 
 * ADC_VOLTAGE_REF_AREF
 * ADC_VOLTAGE_REF_AVCC
 * ADC_VOLTAGE_REF_2_56V
 *
 */
# define ADC_VOLTAGE_REF_AVCC	

////////////////////////////////////////////////////////////////////////
/* Adjustment options : 
 * 
 * ADC_LEFT_ADJUST
 * ADC_RIGHT_ADJUST
 *
 */
# define ADC_RIGHT_ADJUST

////////////////////////////////////////////////////////////////////////
/* Prescaler Selections : 
 * 
 * ADC_SCALE_2
 * ADC_SCALE_4
 * ADC_SCALE_8
 * ADC_SCALE_16
 * ADC_SCALE_32
 * ADC_SCALE_64
 * ADC_SCALE_128
 *
 */
# define ADC_SCALE_64

////////////////////////////////////////////////////////////////////////
/* Mode options : 
 * 
 * SINGLE_CON_MODE
 * FREE_RUNNING_MODE : Switching to Free Running
					   mode (ADTS[2:0]=0) will not cause a trigger event,
					    even if the ADC Interrupt Flag is set.
 *
 */
# define SINGLE_CON_MODE

////////////////////////////////////////////////////////////////////////
#endif /* ADC_CONFIG_H_ */