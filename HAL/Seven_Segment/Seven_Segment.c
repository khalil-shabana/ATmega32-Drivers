/*
 * Seven_Segment.c
 *
 * Created: 7/31/2022 1:49:56 AM
 *  Author: Khalil
 */ 


#include "Seven_Segment.h"

 void seven_seg_init() /* config. of 7-segment and setting pins to be o/p */
 {
	 /* Assuming the decoder is connected to GROUP_C (pins: 4,5,6,7) */
	 IO_WritePinDir(GROUP_C, PIN_4, OUTPUT); // A pin of decoder (assume that ,using GROUP_C)
	 IO_WritePinDir(GROUP_C, PIN_5, OUTPUT); //B
	 IO_WritePinDir(GROUP_C, PIN_6, OUTPUT); //C
	 IO_WritePinDir(GROUP_C, PIN_7, OUTPUT); //D
	 
	 IO_WritePinDir(GROUP_C, PIN_3, OUTPUT); //Enable1 //left
	 IO_WritePinDir(GROUP_C, PIN_2, OUTPUT); //Enable2 //Right
 }
 
 void seven_seg_Enable1()
 {
	 IO_WritePinVal(GROUP_C, PIN_3, LOW);
 }
 
 void seven_seg_Enable2()
 {
	 IO_WritePinVal(GROUP_C, PIN_2, LOW);
 }
 
 void seven_seg_Disable1()
 {
	 IO_WritePinVal(GROUP_C, PIN_3, HIGH);
 }
 
 void seven_seg_Disable2()
 {
	 IO_WritePinVal(GROUP_C, PIN_2, HIGH);
 }
 
 void seven_seg_write(u8_t value)
 {
	 if(value < 10)
	 {
	
		 //3 -> 0b 0000 1001
		 //             DCBA
		 IO_WritePinVal(GROUP_C, PIN_4, GET_BIT(value,0)); //A = 1-st bit of the value
		 IO_WritePinVal(GROUP_C, PIN_5, GET_BIT(value,1)); //B = 2-nd bit of the value
		 IO_WritePinVal(GROUP_C, PIN_6, GET_BIT(value,2)); //C = 3-rd bit of the value
		 IO_WritePinVal(GROUP_C, PIN_7, GET_BIT(value,3)); //D = 4-th bit of the value
	 }
 }