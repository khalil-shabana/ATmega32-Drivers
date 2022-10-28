/*
 * SPI.c
 *
 * Created: 9/19/2022 2:56:09 AM
 *  Author: Khalil
 */ 

#include "SPI.h"

///// Pointer to function that will be called in ISR 
static void (*SPI_Fptr) (void) = NULLPTR;

///// Initialization with structure as a parameter defined in SPI_Confg.h
void SPI_Init()
{	
	/***************** SPI Enabel *****************/
	#if (SPI_ENABLE == SPI_ON)
		SET_BIT(SPCR_reg,SPE);
		
	#elif (SPI_ENABLE == SPI_OFF)
		CLEAR_BIT(SPCR_reg,SPE);
		
	#endif
	
	/***************** SPI Interrupt *****************/
	#if (SPI_INTERRUPT == SPI_INT_ENABLE)
		SET_BIT(SPCR_reg,SPIE);

	#elif (SPI_INTERRUPT == SPI_INT_DISABLE)
		CLEAR_BIT(SPCR_reg,SPIE);
		
	#endif
	
	/***************** Data Order *****************/
	#if (SPI_DATA_ORDER == SPI_LSB_FIRST)
		SET_BIT(SPCR_reg,DORD);
		
	#elif (SPI_DATA_ORDER == SPI_MSB_FIRST)
		CLEAR_BIT(SPCR_reg,DORD);
		
	#endif
	
	/***************** SPI Mode Master/Slave *****************/
	#if (SPI_MODE == SPI_MASTER)
		SET_BIT(SPCR_reg,MSTR);
		
	#elif (SPI_MODE == SPI_SLAVE)
		CLEAR_BIT(SPCR_reg,MSTR);
		
	#endif
	
	/***************** Clock Polarity (CPOL) *****************/
	#if (SPI_CLK_POL == SPI_IDLE_LOW)
		CLEAR_BIT(SPCR_reg,CPOL);
		
	#elif (SPI_CLK_POL == SPI_IDLE_HIGH)
		SET_BIT(SPCR_reg,CPOL);
		
	#endif
	
	/***************** Setting Sampling Edge (CPHA) *****************/
	#if (SPI_SAMPLING_EDGE == SPI_SAMPLING_AT_LEADING_EDGE)
		CLEAR_BIT(SPCR_reg,CPHA);
		
	#elif (SPI_SAMPLING_EDGE == SPI_SAMPLING_AT_TRALLING_EDGE)
		SET_BIT(SPCR_reg,CPHA);
		
	#endif
	
	/***************** SPI Clock Frequency (Prescaler) ((((MASTR onlyy))) *****************/
	SPCR_reg |= SPI_SCK_FREQ;
	
	/***************** SPI Double Speed Mode (((in Master case))) *****************/
	#if (SPI_SPEED == SPI_NORMAL_SPEED)
		CLEAR_BIT(SPSR_reg,SPI2X);
		
	#elif (SPI_SPEED == SPI_DOUBLE_SPEED)
		SET_BIT(SPSR_reg,SPI2X);
		
	#endif
}


///// Sending and Receiving a byte (these two operation occurs in same time)
u8_t SPI_SEND_AND_RECEIVE(u8_t SPI_u8Data)
{
	SPDR_reg = SPI_u8Data;	//sending data
	while (!(GET_BIT(SPSR_reg,SPIF)));
	return SPDR_reg;  //receiving data
}

u8_t SPI_CHECK_COLLISION(void)
{
	u8_t Local_u8CollStatus;
	Local_u8CollStatus= GET_BIT(SPSR_reg,WCOL);
	return Local_u8CollStatus;
}
void SPI_SetCallBack(void (*ISR_Ptr) (void))
{
	SPI_Fptr = ISR_Ptr ;
}

ISR (SPI_STC_vector)
{
	if(SPI_Fptr != NULLPTR)
	{
		SPI_Fptr();
	}
}