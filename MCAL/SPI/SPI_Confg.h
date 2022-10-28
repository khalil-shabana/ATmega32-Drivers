/*
 * SPI_Confg.h
 *
 * Created: 9/19/2022 3:28:28 AM
 *  Author: Khalil
 */ 


#ifndef SPI_CONFG_H_
#define SPI_CONFG_H_


/***************** SPI Enabel *****************/
/*
 * SPI_ON 
 * SPI_OFF
 */
#define SPI_ENABLE				SPI_ON

/***************** SPI Mode *****************/
/*
 * SPI_MASTER 
 * SPI_SLAVE
 */
#define SPI_MODE			   SPI_MASTER

/***************** SPI Interrupt *****************/
/*
 * SPI_INT_ENABLE 
 * SPI_INT_DISABLE
 */
#define SPI_INTERRUPT		   SPI_INT_ENABLE

/***************** Data Order *****************/
/*
 * SPI_LSB_FIRST 
 * SPI_MSB_FIRST
 */
#define SPI_DATA_ORDER		   SPI_LSB_FIRST

/***************** Clock Polarity  *****************/
/*
 * SPI_IDLE_LOW 
 * SPI_IDLE_HIGH
 */
#define SPI_CLK_POL			   SPI_IDLE_LOW

/***************** Setting Sampling Edge *****************/
/* 
 * SPI_SAMPLING_AT_LEADING_EDGE 
 * SPI_SAMPLING_AT_TRALLING_EDGE
 */
#define SPI_SAMPLING_EDGE	   SPI_SAMPLING_AT_LEADING_EDGE

/***************** SPI Clock Frequency (Prescaler) ((((MASTR onlyy))) *****************/
/* 
 * Fosc_div_4	 
 * Fosc_div_16  
 * Fosc_div_64  
 * Fosc_div_128 
 */
#define SPI_SCK_FREQ		   Fosc_div_4

/***************** SPI Double Speed Mode (((in Master case))) *****************/
/*
 * SPI_NORMAL_SPEED
 * SPI_DOUBLE_SPEED
 */
#define SPI_SPEED			   SPI_NORMAL_SPEED
 

#endif /* SPI_CONFG_H_ */