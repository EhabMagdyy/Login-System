/*****************************************************
************    Author: Ehab Magdy		**************
************	SWC	  : lcd.h			**************
************	Data  : 28 Aug, 2023	**************
******************************************************/

#ifndef LCD_H
#define LCD_H

/******************** Includes ***********************/
#include "../../Library/STD_Types.h"

/***************** Macro definitions *****************/
#define LCD_DATA_PORT 		DIO_PORTC
#define	LCD_CONTROL_PORT	DIO_PORTA

#define LCD_RS_PIN			DIO_PIN1
#define LCD_EN_PIN			DIO_PIN2

#define LCD_Function_SET		0b00111000
#define LCD_DISPLAY_ON			0b00001100
#define LCD_CLEAR				0b00000001
#define LCD_INCREMENT_SHIFT_OFF	0b00000110
#define LCD_SHIFT_RIGHT         0b00011100

#define LCD_CGRAM				0b01000000
#define LCD_DDRAM				0b10000000

#define ROW1			1
#define ROW2			2
#define ROW3			3
#define ROW4			4

/*************** Functions Decelerations ***************/
void LCD_voidInit(void);
void LCD_voidSendCommand(u8 command);
void LCD_voidSendChar(u8 data);
void LCD_voidSendCharPos(u8 row, u8 col, u8 data);
void LCD_voidSendString(u8 *string);
void LCD_voidSendStringPos(u8 row, u8 col, u8 *string);
void LCD_voidDrawCharacter(u8 *ch, u8 pos);
void LCD_voidSetCursor(u8 row, u8 col);
void LCD_voidSendNumberPos(u8 row , u8 col, u32 number);

#endif /* LCD_H */
