/*
 * SPI.h
 *
 * Created: 9/19/2022 2:55:59 AM
 *  Author: Khalil
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "Data_types.h"
#include "Bit_Mask.h"
#include "ATmega32_Registers.h"
#include "SPI_Confg.h"

typedef enum{
	SPI_INT_ENABLE,
	SPI_INT_DISABLE
}SPI_Interrupt_t;

typedef enum{
	SPI_ON,
	SPI_OFF
}SPI_Enable_t;

typedef enum{
	SPI_LSB_FIRST,
	SPI_MSB_FIRST
}SPI_DATA_ORDER_t;

typedef enum{
	SPI_MASTER,
	SPI_SLAVE
}SPI_MODE_t;

typedef enum{
	SPI_IDLE_LOW,
	SPI_IDLE_HIGH
}SPI_CLK_POL_t;

typedef enum{
	SPI_SAMPLING_AT_LEADING_EDGE,
	SPI_SAMPLING_AT_TRALLING_EDGE
}SPI_SAMPLING_EDGE_t;

/*For Master only*/
typedef enum{
	Fosc_div_4	 =0b00,
	Fosc_div_16  =0b01,
	Fosc_div_64  =0b10,
	Fosc_div_128 =0b11
}SPI_SCK_FREQUENCY_t;

typedef enum{
	SPI_NORMAL_SPEED,
	SPI_DOUBLE_SPEED
}SPI_SPEED_t;

struct SPI_configuration_Struct{
	SPI_Enable_t		SPI_ENABLE;
	SPI_MODE_t				SPI_MODE;
	SPI_Interrupt_t		SPI_INTERRUPT;
	SPI_DATA_ORDER_t		SPI_DATA_ORDER;
	SPI_CLK_POL_t			SPI_CLK_POL;
	SPI_SAMPLING_EDGE_t	SPI_SAMPLING_EDGE;
	SPI_SCK_FREQUENCY_t	SPI_SCK_FREQ;
	SPI_SPEED_t			SPI_SPEED;
};

void SPI_Init();

u8_t SPI_SEND_AND_RECEIVE(u8_t SPI_u8Data);
u8_t SPI_CHECK_COLLISION(void);
void SPI_SetCallBack(void (*ISR_Ptr) (void));




#endif /* SPI_H_ */