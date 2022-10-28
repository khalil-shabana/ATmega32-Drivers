/*
 * ATmega32_Registers.h
 *
 * Created: 8/1/2022 1:38:41 AM
 *  Author: Khalil
 */ 


#ifndef ATMEGA32_REGISTERS_H_
#define ATMEGA32_REGISTERS_H_
 

/* DIO_Registers */

#define PORTA_reg  *((volatile unsigned char* const)0X3B)
#define DDRA_reg   *((volatile unsigned char* const)0X3A)
#define PINA_reg   *((volatile unsigned char* const)0X39)

#define PORTB_reg  *((volatile unsigned char* const)0X38)
#define DDRB_reg   *((volatile unsigned char* const)0X37)
#define PINB_reg   *((volatile unsigned char* const)0X36)

#define PORTC_reg  *((volatile unsigned char* const)0X35)
#define DDRC_reg   *((volatile unsigned char* const)0X34)
#define PINC_reg   *((volatile unsigned char* const)0X33)

#define PORTD_reg  *((volatile unsigned char* const)0X32)
#define DDRD_reg   *((volatile unsigned char* const)0X31)
#define PIND_reg   *((volatile unsigned char* const)0X30)
/********************************************************************************************************/


/* ADC_Registers */

#define ADMUX_reg  *((volatile unsigned char* const)0X27) // ADC Multiplexer Selection Register

#define MUX0  0		//*
#define MUX1  1		//*
#define MUX2  2		// MUX4:0: Analog Channel and Gain Selection Bits
#define MUX3  3		//*
#define MUX4  4		//*

#define ADLAR 5		// ADC Left Adjust Result: ADLAR = 0 -> start with lsb in ADCL toward ADCH
											// ADLAR = 1 -> start with bit no.6 in ADCL toward ADCH

#define REFS0 6		// REFS1:0: Reference Selection Bits
#define REFS1 7		//*

#define ADCSRA_reg *((volatile unsigned char* const)0X26) //ADC Control and Status Register A
#define ADPS0 0		//*
#define ADPS1 1		// ADPS2:0: ADC Prescaler Select Bits
#define ADPS2 2		//*
#define ADIE  3		// ADC Interrupt Enable
#define ADIF  4		// ADC Interrupt Flag
#define ADATE 5		// ADC Auto Trigger Enable
#define ADSC  6		// ADC Start Conversion
#define ADEN  7		// ADC Enable

#define ADCL_reg   *((volatile unsigned char* const)0X24)
#define ADCH_reg   *((volatile unsigned char* const)0X25)
/********************************************************************************************************/


/*External Interrupt */

#define MCUCR_reg  *((volatile unsigned char* const)0X55) //MCU Control Register:
#define ISC00 0										      //Bit 3, 2 – ISC11, ISC10: Interrupt Sense Control1 Bit 1 and Bit 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

#define MCUCSR_reg *((volatile unsigned char* const)0X54) //MCU Control and Status Register:
#define ISC2 6											  //Bit 6 – ISC2: Interrupt Sense Control2
															
#define GICR_reg   *((volatile unsigned char* const)0X5B) //General Interrupt Control Register(masking Reg.)
#define INT1 7
#define INT0 6
#define INT2 5

#define GIFR_reg   *((volatile unsigned char* const)0X5A) //General Interrupt Flag Register
#define INTF1 7
#define INTF0 6
#define INTF2 5
/********************************************************************************************************/

/* Timer 0 */

#define TCCR0_reg  *((volatile unsigned char* const)0X53)
#define FOC0	7
#define WGM00	6
#define COM01	5
#define COM00	4
#define WGM01	3
#define CS02	2
#define CS01	1
#define CS00	0

#define TCNT0_reg  *((volatile unsigned char* const)0X52) //Timer Counter Register
#define SPMCR_reg  *((volatile unsigned char* const)0X57)
#define TIFR_reg   *((volatile unsigned char* const)0X58)

#define TIMSK_reg  *((volatile unsigned char* const)0X59)
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0
/********************************************************************************************************/

/*TIMER 1*/

#define ICR1_reg   *((volatile unsigned short* )0x46)
#define ICR1L_reg  *((volatile unsigned char* const)0X46)
#define ICR1H_reg  *((volatile unsigned char* const)0X47)

#define OCR1B_reg  *((volatile unsigned short*)0x48)
#define OCR1BL_reg *((volatile unsigned char* const)0X48)
#define OCR1BH_reg *((volatile unsigned char* const)0X49)

#define TCNT1_reg  *((volatile unsigned short*)0x4C)
#define TCNT1L_reg *((volatile unsigned char* const)0X4C)
#define TCNT1H_reg *((volatile unsigned char* const)0X4D)

#define OCR1A_reg  *((volatile unsigned short*)0x4A)
#define OCR1AL_reg *((volatile unsigned char* const)0X4A)
#define OCR1AH_reg *((volatile unsigned char* const)0X4B)

#define OSCCAL_reg *((volatile unsigned char* const)0X51)

#define SFIOR_reg  *((volatile unsigned char* const)0X50)
#define ADTS2			7
#define ADTS1			6
#define ADTS0			5
#define Reserved_Bit	4
#define ACME			3
#define PUD				2
#define PSR2			1
#define PSR10			0

#define TCCR1A_reg *((volatile unsigned char* const)0X4F)
#define COM1A1			7
#define COM1A0			6
#define COM1B1			5
#define COM1B0			4
#define FOC1A			3
#define FOC1B			2
#define WGM11			1
#define WGM10			0

#define TCCR1B_reg *((volatile unsigned char* const)0X4E)
#define ICNC1			7
#define ICES1			6
#define RESERVEDX		5
#define WGM13			4
#define WGM12			3
#define CS12			2
#define CS11			1
#define CS10			0


/********************************************************************************************************/

/* Timer 2 */

#define TCCR2_reg  *((volatile unsigned char* const)0X45)
#define TCNT2_reg  *((volatile unsigned char* const)0X44)
#define OCR2_reg   *((volatile unsigned char* const)0X43)
#define ASSR_reg   *((volatile unsigned char* const)0X42)
#define WDTCR_reg  *((volatile unsigned char* const)0X41)
#define TCCR1B_reg *((volatile unsigned char* const)0X4E)

/******************************************************************************/


/* USART I/O Data Register */
#define UDR_reg    *((volatile unsigned char* const)0X2C)

/* USART Control and Status Register A */
#define UCSRA_reg  *((volatile unsigned char* const)0X2B)
#define RXC		7
#define TXC		6
#define UDRE	5
#define FE		4
#define DOR		3
#define PE		2
#define U2X		1
#define MPCM	0

/* USART Control and Status Register B */
#define UCSRB_reg  *((volatile unsigned char* const)0X2A)
#define RXCIE	7
#define TXCIE	6
#define UDRIE	5
#define RXEN	4
#define TXEN	3
#define UCSZ2	2
#define RXB8	1
#define TXB8	0

/* USART Baud Rate Register Low */
#define UBRRL_reg  *((volatile unsigned char* const)0X29)

/* USART Baud Rate Register High */
#define UBRRH_reg  *((volatile unsigned char* const)0X40)

/* USART Control and Status Register C */
#define UCSRC_reg  *((volatile unsigned char* const)0X40)
#define URSEL	7
#define UMSEL	6
#define UPM1	5
#define UPM0	4
#define USBS	3
#define UCSZ1	2
#define UCSZ0	1
#define UCPOL	0
/* If URSEL is zero during a write operation, the UBRRH value will be updated.
   If URSEL is one, the UCSRC setting will be updated.
 */
/******************************************************************************/

/* SPI */
/* SPI Control Register */
#define SPCR_reg   *((volatile unsigned char* const)0X2D)
#define SPIE	7	/* SPI Interrupt Enable: This bit causes the SPI interrupt to be executed if SPIF bit in the SPSR Register is set and the if
					   the global interrupt enable bit in SREG is set. */
					   
#define SPE		6	// SPI Enable: This bit must be set to enable any SPI operations.

#define DORD	5	/* Data Order: When the DORD bit is written to one, the LSB of the data word is transmitted first
								   When the DORD bit is written to zero, the MSB of the data word is transmitted first.*/

#define MSTR	4	/* Master/Slave Select: selects Master SPI mode when written to one,
											and Slave SPI mode when written logic zero.*/
											
#define CPOL	3	/* Clock Polarity: When this bit is written to one, SCK is high when idle,
									   When CPOL is written to zero, SCK is low.*/

#define CPHA	2	/* Clock Phase:  determine if data is sampled on the leading (first) or
									 trailing (last) edge of SCK*/
									
#define SPR1	1
#define SPR0	0	// SPI Clock Rate Select 1 and 0: These two bits control the SCK rate of the device configured as a Master.

/* SPI Status Register */
#define SPSR_reg   *((volatile unsigned char* const)0X2E)
#define SPIF	7	// SPI Interrupt Flag: When a serial transfer is complete, the SPIF Flag is set.
#define WCOL	6	// Write COLlision Flag:The WCOL bit is set if the SPI Data Register (SPDR) is written during a data transfer.
#define Resev5	5
#define Resev4	4
#define Resev3	3	//  Bit 5..1: These bits are reserved bits in the ATmega32 and will always read as zero.
#define Resev2	2
#define Resev1	1
#define SPI2X	0	// Double SPI Speed Bit:

/* SPI I/O Data Register */
#define SPDR_reg   *((volatile unsigned char* const)0X2F)
/* Writing to the register initiates data transmission.
Reading the register causes the Shift Register Receive buffer to be read. */
/******************************************************************************/

/* EEPROM Control Register */
#define EECR_reg   *((volatile unsigned char* const)0X3C)

/* EEPROM Data Register */
#define EEDR_reg   *((volatile unsigned char* const)0X3D)

/* EEPROM Address Register */
#define EEARH_reg  *((volatile unsigned char* const)0X3F)
#define EEARL_reg  *((volatile unsigned char* const)0X3E)
/******************************************************************************/

/* TWI stands for "Two Wire Interface" or "TWI Was I2C(tm)" */

#define TWBR_reg   *((volatile unsigned char* const)0X20) // TWI Bit Rate Register
/* Bits [7:0]- TWBR selects the division factor for the bit rate generator.
The bit rate generator is a frequency divider which generates the SCL clock frequency in the Master modes */

#define TWCR_reg   *((volatile unsigned char* const)0X56) // TWI Control Register
#define TWINT	7   /* TWI Interrupt Flag: This bit is set by hardware when the TWI has finished its current job and expects application software response.
				     * The TWINT Flag must be cleared by software by writing a logic one to it. Note that this flag is not
					   automatically cleared by hardware when executing the interrupt routine. */

#define TWEA	6   /* TWI Enable Acknowledge Bit: If the TWEA bit is written to one, the ACK pulse is generated on the TWI bus.
												 By writing the TWEA bit to zero, the device can be virtually disconnected from the Two-wire Serial Bus temporarily. */

#define TWSTA	5	/* TWI START Condition Bit: The application writes the TWSTA bit to one when it desires to become a master on the Twowire Serial Bus.
					 * TWSTA must be cleared by software when the START condition has been transmitted. */

#define TWSTO	4	/* TWI STOP Condition Bit: Writing the TWSTO bit to one in Master mode will generate a STOP condition on the Two-wire Serial Bus.
					 * When the STOP condition is executed on the bus, the TWSTO bit is cleared automatically. */

#define TWWC	3	/* TWI Write Collision Flag: The TWWC bit is set when attempting to write to the TWI Data Register – TWDR when TWINT is low.
												 This flag is cleared by writing the TWDR Register when TWINT is high. */

#define TWEN	2	/* TWI Enable Bit: The TWEN bit enables TWI operation and activates the TWI interface.
									   If TWEN is written to one, the TWI takes control over the I/O pins connected to the SCL and SDA pins.
									   Else if is written to zero, TWI is switched off. */
#define Res		1	//Reserved Bit : always == zero

#define TWIE	0	/* TWI Interrupt Enable */

#define TWSR_reg   *((volatile unsigned char* const)0X21)
#define TWS7	7	// Bits [7:3] – TWS: TWI Status
#define TWS6	6
#define TWS5	5		
#define TWS4	4
#define TWS3	3
#define xx		2
#define TWPS1	1	// Bits [1:0] – TWPS: TWI Prescaler Bits
#define TWPS0	0	// These bits can be read and written, and control the bit rate prescaler.

#define TWDR_reg   *((volatile unsigned char* const)0X23) // TWI Data Register
/* These eight bits contain the next data byte to be transmitted, or the latest data byte received on
the Two-wire Serial Bus. */

#define TWAR_reg   *((volatile unsigned char* const)0X22) // TWI (Slave) Address Register
// Bits 7..1 :These seven bits constitute the slave address of the TWI unit. 

#define TWGCE	0	/*TWI General Call Recognition Enable Bit: If set, this bit enables the recognition of a General Call given over the Two-wire Serial Bus.*/

/******************************************************************************/

/******************************************************************************/
#define SREG_reg   *((volatile unsigned char* const)0X5F)
#define SPH_reg    *((volatile unsigned char* const)0X5E)
#define SPL_reg    *((volatile unsigned char* const)0X5D)
#define OCR0_reg   *((volatile unsigned char* const)0X5C)
#define OCDR_reg   *((volatile unsigned char* const)0X51)
#define ACSR_reg   *((volatile unsigned char* const)0X28)
/******************************************************************************/

/* Interrupt vectors */
#define INT0_vector				__vector_1
/* External Interrupt Request 1 */
#define INT1_vector				__vector_2
/* External Interrupt Request 2 */
#define INT2_vector				__vector_3
/* Timer/Counter2 Compare Match */
#define TIMER2_COMP_vector		__vector_4
/* Timer/Counter2 Overflow */
#define TIMER2_OVF_vector		__vector_5
/* Timer/Counter1 Capture Event */
#define TIMER1_CAPT_vector		__vector_6
/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPA_vector		__vector_7
/* Timer/Counter1 Compare Match B */
#define TIMER1_COMPB_vector		__vector_8
/* Timer/Counter1 Overflow */
#define TIMER1_OVF_vector		__vector_9
/* Timer/Counter0 Compare Match */
#define TIMER0_COMP_vector		__vector_10
/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vector		__vector_11
/* Serial Transfer Complete */
#define SPI_STC_vector			__vector_12
/* USART, Rx Complete */
#define UART_RXC_vector			__vector_13
/* USART Data Register Empty */
#define UART_UDRE_vector		__vector_14
/* USART, Tx Complete */
#define UART_TXC_vector			__vector_15
/* ADC Conversion Complete */
#define ADC_vector				__vector_16
/* EEPROM Ready */
#define EE_RDY_vector			__vector_17
/* Analog Comparator */
#define ANA_COMP_vector			__vector_18
/* 2-wire Serial Interface */
#define TWI_vector				__vector_19
/* Store Program Memory Ready */
#define CRM_RDY_vector			__vector_20
/* Bad interrupt */
#define BAD_vector				__vector_default

/*interrupt functions*/
//assembly instructions that will be needed
#define sei()  __asm__ __volatile__ ("sei" ::)  //open global interrupt manually,  this is done after context switching 
#define cli()  __asm__ __volatile__ ("cli" ::)	//close global interrupt
#define reti()  __asm__ __volatile__ ("reti" ::) 

#define ISR_NOBLOCK    __attribute__((interrupt)) //auto. open global interrupt, this is done before context switching 
#define ISR_NAKED      __attribute__((naked)) /*compiler don't make context switching 
or adding (reti) instruction at the end of the interrupt function*/

#define ISR(vector,...)            \
void vector (void) __attribute__ ((signal))__VA_ARGS__ ; \
void vector (void)



#endif /* ATMEGA32_REGISTERS_H_ */