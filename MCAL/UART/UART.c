/*
 * UART.c
 *
 * Created: 9/13/2022 12:16:24 AM
 *  Author: Khalil
 */ 
#include "UART.h"
#include "UART_config.h"

static void (*TX_Fptr)(void) = NULLPTR;
static void (*RX_Fptr)(void) = NULLPTR;

/************************* Array of  UBRR values ***************************/
const u16_t BaudRateArray[SPEED_MODES][TOTAL_CPU_F][TOTAL_BAUD_RATE]=
{							//2				//3				//6
	{ 
		{103, 51, 25, 16, 12,  8},{207,103, 51, 34, 25, 16},{416,207,103, 68 ,51, 34} 
	},
	{ 
		{207,103, 51, 34, 25, 16},{416,207,103, 68 ,51, 34},{832,416,207,138,103, 68} 
	}
};

void UART_INIT(void)
{
	u8_t  UCSRC_var = 0;
	u16_t UBRR_var	= 0;
/***************************** SPEED ***************************/
#if (SPEED == NORMAL_SPEED)
CLEAR_BIT(UCSRA_reg,U2X);

#elif (SPEED == DOUBLE_SPEED)
SET_BIT(UCSRA_reg,U2X);

#endif

/******************* BAUD RATE *****************************/
u16_t UBRR_val= BaudRateArray[SPEED][CPU_F][BUAD_RATE];
UBRRH_reg = (u8_t)(UBRR_val>>8);
UBRRL_reg = (u8_t)(UBRR_val);

//****************** SET URSEL to write data to UCSRC register ***************/
SET_BIT(UCSRC_var,URSEL); //1000 0000

/*************** Sync. mode *************************/
#if (SYNC_MODE == ASYNCH)
CLEAR_BIT(UCSRC_var,UMSEL);

#elif (SYNC_MODE == SYNCH)
SET_BIT(UCSRC_var,UMSEL);

#endif

/******************* Parity mode *************************/
#if (PARITY_MODE == NO_PARITY)
CLEAR_BIT(UCSRC_var,UPM0);
CLEAR_BIT(UCSRC_var,UPM1);

#elif (PARITY_MODE == EVEN_PARITY)
CLEAR_BIT(UCSRC_var,UPM0);
SET_BIT(UCSRC_var,UPM1);

#elif (PARITY_MODE == ODD_PARITY)
SET_BIT(UCSRC_var,UPM0);
SET_BIT(UCSRC_var,UPM1);

#endif

/*************** # of data bits ********************/
#if (NO_DATA_BITS == _5_DATA_BITS)
CLEAR_BIT (UCSRC_var,UCSZ0);
CLEAR_BIT (UCSRC_var,UCSZ1);
CLEAR_BIT (UCSRB_reg,UCSZ2);

#elif (NO_DATA_BITS == _6_DATA_BITS)
SET_BIT (UCSRC_var,UCSZ0);
CLEAR_BIT (UCSRC_var,UCSZ1);
CLEAR_BIT (UCSRB_reg,UCSZ2);

#elif (NO_DATA_BITS == _7_DATA_BITS)
CLEAR_BIT (UCSRC_var,UCSZ0);
SET_BIT (UCSRC_var,UCSZ1);
CLEAR_BIT (UCSRB_reg,UCSZ2);

#elif (NO_DATA_BITS == _8_DATA_BITS)
SET_BIT (UCSRC_var,UCSZ0);
SET_BIT (UCSRC_var,UCSZ1);
CLEAR_BIT (UCSRB_reg,UCSZ2);

#elif (NO_DATA_BITS == _9_DATA_BITS)
SET_BIT (UCSRC_var,UCSZ0);
SET_BIT (UCSRC_var,UCSZ1);
SET_BIT (UCSRB_reg,UCSZ2);

#endif

/*************** # of stop bits ***************/
#if (NO_STOP_BITS == ONE_STOP_BIT)
CLEAR_BIT (UCSRC_var,USBS);

#elif (NO_STOP_BITS == TWO_STOP_BIT)
SET_BIT (UCSRC_var,USBS);

#endif
//***************** Set UCSRC value   *******************************/
UCSRC_reg = UCSRC_var;

//************************ Enable *******************************/
//enable UART  Rx:
SET_BIT(UCSRB_reg,RXEN);
//enable UART  Tx:
SET_BIT(UCSRB_reg,TXEN);
}

/*************************** Send and receive functions using interrupt ***************************/
void UART_SEND_BYTE(u8_t uart_data)
{
	/*UDRE flag is set when the buffer is empty and ready
	for transmitting a new byte so wait until this flag is set to one 
	and it will cleared by hardware when u write  new data to buffer.*/
	while (!(GET_BIT(UCSRA_reg,UDRE)));
	UDR_reg = uart_data;
}

u8_t UART_RECEIVE_BYTE()
{
	/* This flag bit is set when there are unread data in the receive buffer 
	and cleared when the receive buffer is empty (that is, does not contain any unread data). */
	while (!(GET_BIT(UCSRA_reg, RXC)));
	return UDR_reg;
}

u8_t UART_SEND_BYTE_NO_WAIT(u8_t uart_data)
{
	if (!(GET_BIT(UCSRA_reg,UDRE)))
	{
		UDR_reg = uart_data;
		return 1;
	} 
	else
	{
		return 0;
	}
}
u8_t UART_RECEIVE_BYTE_NO_WAIT(u8_t* pData)
{
	if ((GET_BIT(UCSRA_reg, RXC)))
	{
		*pData= UDR_reg;
		return 1;
	}
	else
	{
		return 0;
	}
}
/*************************** Interrupt functions ***************************/

void UART_RX_INT_Enable(void)
{
	SET_BIT(UCSRB_reg,RXCIE);
}
void UART_RX_INT_Disable(void)
{
	CLEAR_BIT(UCSRB_reg,RXCIE);
}

void UART_TX_INT_Enable(void)
{
	SET_BIT(UCSRB_reg,TXCIE);
}
void UART_TX_INT_Disable(void)
{
	CLEAR_BIT(UCSRB_reg,TXCIE);
}

/*************************** Set call-back functions ***************************/
void UART_TX_SetCallBack(void (*Local_Fptr) (void))
{
	TX_Fptr = Local_Fptr;
}
void UART_RX_SetCallBack(void (*Local_Fptr) (void))
{
	RX_Fptr = Local_Fptr;
}
/*************************** ISR ***************************/
ISR (UART_TXC_vector)
{
	if (TX_Fptr != NULLPTR)
	{
		TX_Fptr();
	}
}

ISR (UART_RXC_vector)
{
	if (RX_Fptr != NULLPTR)
	{
		RX_Fptr();
	}
}

// NOW, We can build send and receive function that not depend on polling ...
/*************************** Send and receive functions using interrupt ***************************/
void UART_SEND_BYTE_WITH_INT(u8_t uart_data)
{
	UDR_reg =uart_data;
}
u8_t UART_RECEIVE_BYTE_WITH_INT(void)
{
	return UDR_reg;
}