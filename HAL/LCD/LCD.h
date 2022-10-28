/*
 * LCD.h
 *
 * Created: 8/1/2022 12:24:40 AM
 *  Author: Khalil
 */ 


#ifndef LCD_H_
#define LCD_H_

#ifndef F_CPU
#define  F_CPU 8000000UL
#endif

#include "IO_ATMEGA32.h"

/* Enable_Signal_ms():
	 function uses the _delay_ms(t) with a variable, rather than a constant..
	 so we will use this workaround */
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
/*____________________________________________________________________________________________________________________*/

/*--------- User layer ---------*/
#define LCD_data_Group GROUP_A
#define LCD_data_DDR   DDRA_reg
#define LCD_data_PORT  PORTA_reg
#define LCD_data_PIN   PINA_reg

#define LCD_ctrl_Group GROUP_A
#define LCD_ctrl_DDR   DDRA_reg  //interested in 3 pins RS, RW and EN
#define LCD_ctrl_PORT  PORTA_reg
#define LCD_ctrl_PIN   PINA_reg

#define LCD_RS   0    //RS is connected to PIN_1 of LCD_ctrl_PORT
#define LCD_RW   1    //RW is connected to PIN_2 of LCD_ctrl_PORT
#define LCD_EN   2    //EN is connected to PIN_3 of LCD_ctrl_PORT

#define LCD_mode 4    //In case of 4-bit mode the higher 4-bit must be used in both lcd and PORT
/*--------- End of User layer ---------*/

		/* LCD Commands */
#define LCD_CLR_DISPLAY		    0x01
#define LCD_RETURN_HOME		    0x02
#define LCD_ENTERY_DEC			0x04
#define LCD_ENTERY_DEC_SH	    0x05
#define LCD_ENTERY_INC			0x06
#define LCD_ENTERY_INC_SH		0x07
#define LCD_DIS_OFF             0x08
#define LCD_DIS_ON_CURSOR_OFF   0x0C	
#define LCD_DIS_ON_CURSOR_ON    0x0E
#define LCD_DIS_ON_CURSOR_BLINK 0x0F
#define LCD_SHL_CURSOR			0x10	
#define LCD_SHR_CURSOR			0x14
#define LCD_SHL_DISPLAY			0x18
#define LCD_SHR_DISPLAY			0x1C
#define LCD_CURSOR_AT_1st_ROW	0x80
#define LCD_CURSOR_AT_2ND_ROW   0xC0
#define LCD_FUN_8BIT_1_LINE		0x30
#define LCD_FUN_8BIT_2_LINE		0x38
#define LCD_FUN_4BIT_1_LINE		0x20
#define LCD_FUN_4BIT_2_LINE		0x28

#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__
#define PIN_of(x) PRIMITIVE_CAT(PIN_, x)     

void Enable_Signal_ms(int delay);
void LCD_init(void);
void LCD_Write_CMD(u8_t cmd);
void LCD_clear_screen(void);
void LCD_goto_pos(u8_t row, u8_t col);
void LCD_print_char(u8_t value);
void LCD_print_string_at_XY(char str[], u8_t row, u8_t col);
void LCD_print_string(char *string);
void LCD_print_number_at_XY(int num, u8_t row, u8_t col);
void LCD_print_number(int n);
void LCD_print_number_4digits(u16_t Number);
void LCD_Generate_CUSTOM_Pattern(u8_t* pattern, u8_t CGRAM_index);
void LCD_print_CUSTOM_pattern(u8_t CGRAM_index, u8_t row, u8_t col);



#endif /* LCD_H_ */