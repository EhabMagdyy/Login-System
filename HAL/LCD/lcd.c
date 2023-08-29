/*****************************************************
************    Author: Ehab Magdy		**************
************	SWC	  : lcd.c			**************
************	Data  : 28 Aug, 2023	**************
******************************************************/

#include "../../Library/STD_Types.h"
#include "../../MCAL/DIO/dio.h"
#include "util/delay.h"

#include "lcd.h"

void LCD_voidInit(void)
{
	/* Data pins -> output */
	DIO_voidSetPortDirection(LCD_DATA_PORT, 0xFF);
	/* RS, RW, EN pins  -> output */
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, LCD_EN_PIN, DIO_DIRECTION_OUTPUT);
	_delay_ms(40);

    /* Set LCD Configurations */
	LCD_voidSendCommand(LCD_Function_SET);
	_delay_us(40);
	LCD_voidSendCommand(LCD_DISPLAY_ON);
	_delay_us(40);
	LCD_voidSendCommand(LCD_CLEAR);
	_delay_ms(2);
	LCD_voidSendCommand(LCD_INCREMENT_SHIFT_OFF);
	_delay_ms(2);
}

void LCD_voidSendCommand(u8 command)
{
	/* RS, E pins  -> output */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_LOW);
	/* send command */
	DIO_voidSetPortValue(LCD_DATA_PORT, command);
	/* Send enable signal */
	/* RS, E pins  -> output */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, DIO_HIGH);
	_delay_us(5);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, DIO_LOW);
}

void LCD_voidSendChar(u8 data)
{
	/* RS, E pins  -> output */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_HIGH);
	/* send data */
	DIO_voidSetPortValue(LCD_DATA_PORT, data);
	/* Send enable signal */
	/* RS, E pins  -> output */
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, DIO_HIGH);
	_delay_us(5);
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_EN_PIN, DIO_LOW);
}

void LCD_voidSendCharPos(u8 row, u8 col, u8 data)
{
	LCD_voidSetCursor(row, col);
	LCD_voidSendChar(data);
}

void LCD_voidSendString(u8 *string)
{
	do{
		LCD_voidSendChar(*string);
	}while(*(++string));
}

void LCD_voidSendStringPos(u8 row, u8 col, u8 *string)
{
	LCD_voidSetCursor(row, col);
	LCD_voidSendString(string);
}


void LCD_voidDrawCharacter(u8 *ch, u8 pos)
{
	LCD_voidSendCommand(LCD_CGRAM + pos * 8);
	_delay_us(50);
	for(u8 char_index = 0 ; char_index < 8 ; char_index++){
		LCD_voidSendChar(ch[char_index]);
	}
	//LCD_voidSendCommand(LCD_DDRAM);	//Set Cursor instead
	LCD_voidSendChar(pos);
}

void LCD_voidSetCursor(u8 row, u8 col)
{
	if(4 >= row && 16 >= col)
	{
		col--;	/* for the user first column is 1, so we should take col-1 */

		switch(row)
		{
			case ROW1:	LCD_voidSendCommand(0x80 + col);	break;
			case ROW2:  LCD_voidSendCommand(0xC0 + col);	break;
			case ROW3:	LCD_voidSendCommand(0x90 + col);	break;
			case ROW4:  LCD_voidSendCommand(0xD0 + col);	break;
			default: 										break;
		}
	}
}

void LCD_voidSendNumberPos(u8 row , u8 col, u32 number)
{
	u8 num_digits = 0;
	u32 temp = number;

	while(temp /= 10){
		num_digits++;
	}

	u8 num_text[10] = {0};

	/* For clearing part of screen when displaying temperature */
	if(num_digits < 2)
		num_text[num_digits+1] = ' ';

	do {
		num_text[num_digits--] = (number % 10) + '0';
	} while(number/=10);

	LCD_voidSendStringPos(row, col, num_text);
}
