/*
 * IO_config.h
 *
 * Created: 8/26/2022 2:57:38 PM
 *  Author: Khalil
 */ 


#ifndef IO_CONFIG_H_
#define IO_CONFIG_H_


/* choose : 0 for input
 *			1 for output
 *			*/

#define PORTA_PIN0_DIR	1
#define PORTA_PIN1_DIR	1
#define PORTA_PIN2_DIR	1
#define PORTA_PIN3_DIR	0
#define PORTA_PIN4_DIR	1
#define PORTA_PIN5_DIR	1
#define PORTA_PIN6_DIR	1
#define PORTA_PIN7_DIR	1

#define PORTB_PIN0_DIR	1
#define PORTB_PIN1_DIR	1
#define PORTB_PIN2_DIR	1
#define PORTB_PIN3_DIR	1
#define PORTB_PIN4_DIR	0
#define PORTB_PIN5_DIR	0
#define PORTB_PIN6_DIR	0
#define PORTB_PIN7_DIR	0

#define PORTC_PIN0_DIR	1
#define PORTC_PIN1_DIR	1
#define PORTC_PIN2_DIR	1
#define PORTC_PIN3_DIR	1
#define PORTC_PIN4_DIR	1
#define PORTC_PIN5_DIR	1
#define PORTC_PIN6_DIR	1
#define PORTC_PIN7_DIR  1

#define PORTD_PIN0_DIR	0
#define PORTD_PIN1_DIR	1
#define PORTD_PIN2_DIR	0
#define PORTD_PIN3_DIR	0
#define PORTD_PIN4_DIR	1
#define PORTD_PIN5_DIR	1
#define PORTD_PIN6_DIR	0
#define PORTD_PIN7_DIR	0

/* choose: (if pin is set to input) :
 * 			1 : Pulled_Up
 *			0 : Floating
 *
 *		 : (if pin is set to output)
 *			1 : HIGH
 *			0 : LOW
 *			*/

#define PORTA_PIN0_INIT 0
#define PORTA_PIN1_INIT 0
#define PORTA_PIN2_INIT 0
#define PORTA_PIN3_INIT 0
#define PORTA_PIN4_INIT 0
#define PORTA_PIN5_INIT 0
#define PORTA_PIN6_INIT 0
#define PORTA_PIN7_INIT 0

#define PORTB_PIN0_INIT 0
#define PORTB_PIN1_INIT 0
#define PORTB_PIN2_INIT 0
#define PORTB_PIN3_INIT 0
#define PORTB_PIN4_INIT 0
#define PORTB_PIN5_INIT 0
#define PORTB_PIN6_INIT 0
#define PORTB_PIN7_INIT 0

#define PORTC_PIN0_INIT 1
#define PORTC_PIN1_INIT 0
#define PORTC_PIN2_INIT 0
#define PORTC_PIN3_INIT 0
#define PORTC_PIN4_INIT 0
#define PORTC_PIN5_INIT 0
#define PORTC_PIN6_INIT 0
#define PORTC_PIN7_INIT 0

#define PORTD_PIN0_INIT 0
#define PORTD_PIN1_INIT 0
#define PORTD_PIN2_INIT 1
#define PORTD_PIN3_INIT 0
#define PORTD_PIN4_INIT 0
#define PORTD_PIN5_INIT 0
#define PORTD_PIN6_INIT 0
#define PORTD_PIN7_INIT 0





#endif /* IO_CONFIG_H_ */