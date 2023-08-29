/*****************************************************
************    Author: Ehab Magdy		**************
************	SWC	  : keypad.c        **************
************	Data  : 28 Aug, 2023	**************
******************************************************/

#include <avr/io.h>
#include "../../MCAL/DIO/dio.h"
#include <util/delay.h>

#include "keypad.h"

u8 keypad_values[4][3] = {
							{'1', '2', '3'},
							{'4', '5', '6'},
							{'7', '8', '9'},
							{'*', '0', '#'}
};

u8 rows_pins[4] = {KEYPAD_ROW_0, KEYPAD_ROW_1, KEYPAD_ROW_2, KEYPAD_ROW_3};
u8 cols_pins[3] = {KEYPAD_COL_0, KEYPAD_COL_1, KEYPAD_COL_2};

void keypad_voidInit(void)
{
	DIO_voidSetPortDirection(KEYPAD_PORT, OUT_ROWS_IN_COLUMNS);
	DIO_voidSetPortValue(KEYPAD_PORT, 0x7F);		/* 0111 1111 */
}

void keypad_voidGetPressedKey(u8* keypad_pressed_key)
{
	u8 RowCounter, ColCounter, Pin_logic;
	*keypad_pressed_key = 0;

	for (RowCounter = 0 ; RowCounter < 4 ; RowCounter++)
	{
		DIO_voidSetPinValue(KEYPAD_PORT, rows_pins[RowCounter], DIO_LOW);

		for (ColCounter = 0 ; ColCounter < 3 ; ColCounter++)
		{
			Pin_logic = DIO_u8GetPinLogic(KEYPAD_PORT, cols_pins[ColCounter]);

			if (DIO_LOW == Pin_logic)
			{
				_delay_ms(20);
				Pin_logic = DIO_u8GetPinLogic(KEYPAD_PORT, cols_pins[ColCounter]);

				while (DIO_LOW == Pin_logic)
				{
					Pin_logic = DIO_u8GetPinLogic(KEYPAD_PORT, cols_pins[ColCounter]);
				}

				*keypad_pressed_key = keypad_values[RowCounter][ColCounter];

				DIO_voidSetPinValue(KEYPAD_PORT, rows_pins[RowCounter], DIO_HIGH);

				return;
			}
			else{/* Nothing */}

		}

		DIO_voidSetPinValue(KEYPAD_PORT, rows_pins[RowCounter], DIO_HIGH);
	}
}
