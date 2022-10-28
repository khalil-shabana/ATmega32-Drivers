/*
 * Seven_Segment.h
 *
 * Created: 7/31/2022 1:49:47 AM
 *  Author: Khalil
 */ 


#ifndef SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_H_

#include "IO_ATMEGA32.h"

/* this code is a driver for two seven segment with decoder */

 void seven_seg_init(); //initiate 7-segment
 
 void seven_seg_write(u8_t value); //write a value on 7-segment
 
 void seven_seg_Enable1();
 
 void seven_seg_Enable2();
 
 void seven_seg_Disable1();
 
 void seven_seg_Disable2();


#endif /* SEVEN_SEGMENT_H_ */