/*
 * LCD.c
 *
 * Created: 8/1/2022 12:24:51 AM
 *  Author: Khalil
 */ 
#include "LCD.h"

void Enable_Signal_ms(int delay)
{
	//EN - High -> LOW
	SET_BIT(LCD_ctrl_PORT,LCD_EN); //High pulse
	_delay_ms(delay);
	CLEAR_BIT(LCD_ctrl_PORT,LCD_EN); //Low pulse
	
}

static u8_t mode4_init_finished ;
void LCD_init(void)
{	
	IO_WritePinDir (LCD_ctrl_Group, PIN_of(LCD_RS), OUTPUT);  //Set RS pin as OUTPUT
	IO_WritePinDir (LCD_ctrl_Group, PIN_of(LCD_RW), OUTPUT);  //Set RW pin as OUTPUT
	IO_WritePinDir (LCD_ctrl_Group, PIN_of(LCD_EN), OUTPUT);  //Set EN pin as OUTPUT
	_delay_ms(2);
	
				/*---------- 8-bit mode initialization ----------*/
	if (LCD_mode == 8)
	{
		IO_WritePortDir(LCD_data_Group,OUTPUT);  //Set data port as OUTPUT
		_delay_ms(30); /* LCD Power ON delay always >30ms */
		
		/*Function Set*/
		LCD_Write_CMD(LCD_FUN_8BIT_2_LINE); // 0011 N=1 F=0 XX
		_delay_ms(1);
		
		/*Display ON/OFF Control*/
		LCD_Write_CMD(LCD_DIS_ON_CURSOR_BLINK); // 0000 1 D=1 C=1 B=1
		_delay_ms(1);
		
		/*Display Clear*/
		LCD_Write_CMD(LCD_CLR_DISPLAY); //0000 0001
		_delay_ms(2);
		
		/*Entry Mode Set*/
		LCD_Write_CMD(LCD_ENTERY_INC); // 0000 01 I/D=1 SH=0
		_delay_ms(2);
				/*---------- End of 8-bit mode initialization ----------*/
		
	}
				/*---------- 4-bit mode initialization ----------*/
	else if (LCD_mode == 4)
	{
		IO_WritePinDir(LCD_data_Group, PIN_4, OUTPUT); //DB4
		IO_WritePinDir(LCD_data_Group, PIN_5, OUTPUT); //BD5
		IO_WritePinDir(LCD_data_Group, PIN_6, OUTPUT); //DB6
		IO_WritePinDir(LCD_data_Group, PIN_7, OUTPUT); //DB7
		_delay_ms(30); /* LCD Power ON delay always >30ms */
		
		mode4_init_finished= 0;
		
		/*Function Set*/
		LCD_Write_CMD(LCD_FUN_4BIT_1_LINE);
		LCD_Write_CMD(LCD_FUN_4BIT_1_LINE);
		LCD_Write_CMD(LCD_CURSOR_AT_1st_ROW);
		_delay_ms(1);
		
		/*Display ON/OFF Control*/
		LCD_Write_CMD(0x00);
		LCD_Write_CMD(0xf0);
		_delay_ms(1);
		
		/*Display Clear*/
		LCD_Write_CMD(0x00);
		LCD_Write_CMD(LCD_SHL_CURSOR);
		_delay_ms(2);
		
		/*Entry Mode Set*/
		LCD_Write_CMD(0x00);
		LCD_Write_CMD(0x60);
		_delay_ms(2);
		
				/*---------- End of 4-bit mode initialization ----------*/
		mode4_init_finished= 1;
	}
}

void LCD_Write_CMD(u8_t cmd)
{
	 IO_WritePinVal(LCD_ctrl_Group, PIN_of(LCD_RS), LOW ); //RS = 0
	 IO_WritePinVal(LCD_ctrl_Group, PIN_of(LCD_RW), LOW ); //RW = 0
	 if (LCD_mode == 8)
	 {
		 LCD_data_PORT = cmd;
		 //EN - High -> LOW
		 Enable_Signal_ms(50);
	 }
	 else if (LCD_mode == 4)
	 {
		 //cmd => 0b 0000 0000 ,(we will take upper nibble then lower nibble
	 	 /* Sending upper nibble */
		 IO_WritePinVal(LCD_data_Group, PIN_4, GET_BIT(cmd,4)); //DB4
		 IO_WritePinVal(LCD_data_Group, PIN_5, GET_BIT(cmd,5)); //DB5
		 IO_WritePinVal(LCD_data_Group, PIN_6, GET_BIT(cmd,6)); //DB6
		 IO_WritePinVal(LCD_data_Group, PIN_7, GET_BIT(cmd,7)); //DB7
		 
		 //EN - High -> LOW
		 Enable_Signal_ms(30);
		 
		 if (mode4_init_finished)
		 {
			 /* Sending lower nibble */
			 IO_WritePinVal(LCD_data_Group, PIN_4, GET_BIT(cmd,0)); //DB4
			 IO_WritePinVal(LCD_data_Group, PIN_5, GET_BIT(cmd,1)); //DB5
			 IO_WritePinVal(LCD_data_Group, PIN_6, GET_BIT(cmd,2)); //DB6
		     IO_WritePinVal(LCD_data_Group, PIN_7, GET_BIT(cmd,3)); //DB7
		 
			 //EN - High -> LOW
			 Enable_Signal_ms(30);
		 }
		_delay_ms(20);
	 }
}

void LCD_clear_screen(void)
{
	LCD_Write_CMD(LCD_CLR_DISPLAY);
}

void LCD_goto_pos(u8_t row, u8_t col)
{
	if (row == 0)
	{
		if (col >=0 && col<16)
		{
			LCD_Write_CMD(LCD_CURSOR_AT_1st_ROW + col);
		}
	}
	else if (row == 1)
	{
		if (col >=0 && col<16)
		{
			LCD_Write_CMD(LCD_CURSOR_AT_2ND_ROW + col);
		}
	}
}
	
	/*u8_t address;
	if (row <2 && col < 16)
	{
		address =(row * 0x40) + col;  //Address of new position is calculated
	}
	//We'll use (Set DDRAM Address) instruction from data-sheet
	address = SET_BIT(address, 7);
	LCD_Write_CMD(address); */	


void LCD_print_char(u8_t value)
{
	IO_WritePinVal(LCD_ctrl_Group, PIN_of(LCD_RS), HIGH ); //RS = 1
	IO_WritePinVal(LCD_ctrl_Group, PIN_of(LCD_RW), LOW ); //RW = 0
	
	if (LCD_mode == 8)
	{
		LCD_data_PORT = value;
		Enable_Signal_ms(2);
	}
	else if (LCD_mode == 4)
	{
		//value => 0b 0000 0000 ,(we will take upper nibble then lower nibble
		/* Sending upper nibble */
		IO_WritePinVal(LCD_data_Group, PIN_4, GET_BIT(value,4)); //DB4
		IO_WritePinVal(LCD_data_Group, PIN_5, GET_BIT(value,5)); //DB5
		IO_WritePinVal(LCD_data_Group, PIN_6, GET_BIT(value,6)); //DB6
		IO_WritePinVal(LCD_data_Group, PIN_7, GET_BIT(value,7)); //DB7
		
		//EN - High -> LOW
		Enable_Signal_ms(1);
		
		/* Sending upper nibble */
		IO_WritePinVal(LCD_data_Group, PIN_4, GET_BIT(value,0)); //DB4
		IO_WritePinVal(LCD_data_Group, PIN_5, GET_BIT(value,1)); //DB5
		IO_WritePinVal(LCD_data_Group, PIN_6, GET_BIT(value,2)); //DB6
		IO_WritePinVal(LCD_data_Group, PIN_7, GET_BIT(value,3)); //DB7
		
		//EN - High -> LOW
		Enable_Signal_ms(20);
		
	}
}

void LCD_print_string_at_XY(char str[],u8_t row, u8_t col)
{
	LCD_goto_pos(row,col);
	int count ; //to count how much char on the row (it should be <=16)
	(row==1)? (count= col+16):(count= col);
	while(*str != 0)
	{		
		if (row == 0 && count == 16) //if happened, goto 2nd row
		{
			LCD_goto_pos(1,0); //row 1 position 0
		}
		else if (row ==1 && (count == 32 || count == 33))  //if happened, clear and show the rest
		{
			LCD_clear_screen();
			LCD_goto_pos(0,0);
			count = 0;
		}
		LCD_print_char(*str);
		count++;
		str++;
	}
}

void LCD_print_string(char *string)
{
	//LCD_Write_CMD(0x02);
	while (*string != '\0')
	{
		LCD_print_char(*string);
		string++;
	}

}
	
void LCD_print_number(int n)
{
	char buffer[12];
	itoa(n,buffer,10);
	LCD_print_string(buffer);
}

void LCD_print_number_4digits(u16_t Number)
{
	LCD_print_number(Number%10000/1000+'0');
	LCD_print_number(Number%1000/100+'0');
	LCD_print_number(Number%100/10+'0');
	LCD_print_number(Number%10/1+'0');
}

void LCD_print_number_at_XY(int num, u8_t row, u8_t col)
{
	char buffer[8];
	sprintf(buffer,"%X",num);   
    /* The string "sum of 10 and 20 is 30" is stored
	   into buffer instead of printing on stdout*/
	LCD_print_string_at_XY(buffer, row, col);
}

void LCD_Generate_CUSTOM_Pattern(u8_t* pattern, u8_t CGRAM_index)
{
	u8_t address;
	u8_t index;
	if (CGRAM_index < 8)
	{
		address = CGRAM_index * 0x08; //address of where patter will be stored in CGRAM
		
		// to set CGRAM in address counter RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	    //								   0   0   0   1  AC5 AC4 AC3 AC2 AC1 AC0
		SET_BIT(address, 6);
		LCD_Write_CMD(address);				
		for (index=0; index<8; index++)
		{
			LCD_print_char(pattern[index]);
		}
		LCD_Write_CMD(0x02); //return home : AC returns to DDRAM			   
		
	}
}


void LCD_print_CUSTOM_pattern(u8_t CGRAM_index, u8_t row, u8_t col)
{
	LCD_goto_pos(row, col);
	LCD_print_char(CGRAM_index);
}