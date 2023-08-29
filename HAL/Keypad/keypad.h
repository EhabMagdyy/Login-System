/*****************************************************
************    Author: Ehab Magdy		**************
************	SWC	  : keypad.h        **************
************	Data  : 28 Aug, 2023	**************
******************************************************/

#ifndef KEYPAD_H
#define KEYPAD_H

/******************** Includes ***********************/
#include "../../Library/STD_Types.h"

/************** Macro definitions ********************/
#define KEYPAD_PORT		DIO_PORTD

#define OUT_ROWS_IN_COLUMNS	0x0F

#define KEYPAD_ROW_0		DIO_PIN0
#define KEYPAD_ROW_1		DIO_PIN1
#define KEYPAD_ROW_2		DIO_PIN2
#define KEYPAD_ROW_3		DIO_PIN3

#define KEYPAD_COL_0		DIO_PIN4
#define KEYPAD_COL_1		DIO_PIN5
#define KEYPAD_COL_2		DIO_PIN6

/*************** Functions Decelerations ***************/
void keypad_voidInit(void);
void keypad_voidGetPressedKey(u8* pressed_key);

#endif /* KEYPAD_H */
