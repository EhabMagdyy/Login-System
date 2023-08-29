/*****************************************************
************    Author: Ehab Magdy		**************
************	SWC	  : app.c			**************
************	Data  : 28 Aug, 2023	**************
******************************************************/


#include "app.h"

int main(void)
{
	/* Initializing drivers */
	ADC_voidInit();
    LCD_voidInit();
    keypad_voidInit();
    DC_Motor_Initiliaze();
    StepMotor_Init();

    /* initializing two leds */
    DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN6, DIO_DIRECTION_OUTPUT);
    DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN7, DIO_DIRECTION_OUTPUT);
    DIO_voidSetPinValue(DIO_PORTA, DIO_PIN6, DIO_LOW);
    DIO_voidSetPinValue(DIO_PORTA, DIO_PIN7, DIO_LOW);

    u8 login_status = 0, keypad_pressed_key = 0;

    login_status = login_system();

	while(1)
	{
		if(LOGIN_DENIED == login_status)
		{
			DIO_voidTogglePinvalue(DIO_PORTA, DIO_PIN7);
			_delay_ms(500);
		}
		/* If login successfully */
		else if(LOGIN_SUCCESSFULLY == login_status)
		{

			LCD_voidSendStringPos(1, 1, "1- Temperature");
			LCD_voidSendStringPos(2, 1, "2- Stepper Motor");
			LCD_voidSendStringPos(3, 1, "3- DC Motor");
			LCD_voidSendStringPos(4, 1, "4- Close");

			do
			{
				keypad_voidGetPressedKey(&keypad_pressed_key);
			} while('1' > keypad_pressed_key || '4' < keypad_pressed_key);

			LCD_voidSendCommand(LCD_CLEAR);

			if(CHIOCE_TEMPERATURE == keypad_pressed_key)
			{
				Read_Temp();
			}
			else if(CHIOCE_STEPPER_MOTOR == keypad_pressed_key)
			{
				Set_Stepper_Motor_Angle();
			}
			else if(CHIOCE_DC_MOTOR == keypad_pressed_key)
			{
				Set_DC_Motor_Direction();
			}
			else if(CHIOCE_CLOSE == keypad_pressed_key)
			{
				LCD_voidSendStringPos(1, 2,"System Closed");
				DIO_voidSetPinValue(DIO_PORTA, DIO_PIN7, DIO_HIGH);

				_delay_ms(2000);

				DIO_voidSetPinValue(DIO_PORTA, DIO_PIN7, DIO_LOW);
				LCD_voidSendCommand(LCD_CLEAR);

				login_status = login_system();
			}
		}
	}

	return 0;
}

u8 login_system(void)
{
	u16 system_password = 1234, entered_password = 0;
	u8 keypad_pressed_key = 0, pass_len = 0, num_of_tries = 0, cursor_index = 12;

	while(3 > num_of_tries)
	{
		LCD_voidSendStringPos(1, 1,"Enter Password:");
		/* Password length = 4 */
		while(4 > pass_len)
		{
			do
			{
				keypad_voidGetPressedKey(&keypad_pressed_key);
			} while('0' > keypad_pressed_key || '9' < keypad_pressed_key);

			/* Taking password from user */
			pass_len++;
			entered_password = (entered_password * 10) + (keypad_pressed_key - '0');
			/* Displaying entered number */
			LCD_voidSendCharPos(2 , ++cursor_index, keypad_pressed_key);
			_delay_ms(250);
			LCD_voidSendCharPos(2 , cursor_index, '*');
		}

		LCD_voidSendCommand(LCD_CLEAR);
		/* If password correct */
		if(entered_password == system_password)
		{
			LCD_voidSendStringPos(1, 1, "Choose option...");
			DIO_voidSetPinValue(DIO_PORTA, DIO_PIN6, DIO_HIGH);

			_delay_ms(1000);

			LCD_voidSendCommand(LCD_CLEAR);
			DIO_voidSetPinValue(DIO_PORTA, DIO_PIN6, DIO_LOW);

			return LOGIN_SUCCESSFULLY;
		}
		else
		{
			if(2 == num_of_tries)
			{
				LCD_voidSendStringPos(1, 2, "Wrong Password");
				LCD_voidSendStringPos(2, 3, "Login Denied");
			}
			else
			{
				LCD_voidSendStringPos(1, 2, "Wrong Password");
				LCD_voidSendCharPos(2, 4, (2-num_of_tries)+'0');
				LCD_voidSendStringPos(2, 5, " Try left");
				/* Resetting variables */
				cursor_index = 12;
				pass_len = 0;
				entered_password = 0;
			}

			DIO_voidSetPinValue(DIO_PORTA, DIO_PIN7, DIO_HIGH);
			_delay_ms(1000);
			LCD_voidSendCommand(LCD_CLEAR);
			DIO_voidSetPinValue(DIO_PORTA, DIO_PIN7, DIO_LOW);

			num_of_tries++;
		}
	}

	return LOGIN_DENIED;
}


void Read_Temp(void)
{
	u16 lm35_value = 0, lm35_value_celisuis = 0;
	u8 keypad_pressed_key = 0;

	LCD_voidSendStringPos(1, 1, "Temperature:   C");
	LCD_voidSendStringPos(4, 1, "4- Back");

	do{

		lm35_value = ADC_u16GetDigitalValue(ADC_CHANNEL_0);
		lm35_value_celisuis = lm35_value * 4.88f;			/* StepSize / Resultion = 5/(2^10) = 4.88 */
		lm35_value_celisuis = round(lm35_value_celisuis/10.0);

		LCD_voidSendNumberPos(1, 13, lm35_value_celisuis);

		keypad_voidGetPressedKey(&keypad_pressed_key);

	} while(!keypad_pressed_key);	/* Press any key -> Back */

	LCD_voidSendCommand(LCD_CLEAR);
}

void Set_DC_Motor_Direction(void)
{
	u8 keypad_pressed_key = 0;

	LCD_voidSendStringPos(1, 1, "1- Rotate CW");
	LCD_voidSendStringPos(2, 1, "2- Rotate CCW");
	LCD_voidSendStringPos(3, 1, "3- Stop motor");
	LCD_voidSendStringPos(4, 1, "4- Back");

	do{
		keypad_voidGetPressedKey(&keypad_pressed_key);

		if(DC_MOTOR_ROTATE_CW == keypad_pressed_key)
		{
			DC_Motor_Move_CW();
		}
		else if(DC_MOTOR_ROTATE_CCW == keypad_pressed_key)
		{
			DC_Motor_Move_CCW();
		}
		else if(DC_MOTOR_STOP == keypad_pressed_key)
		{
			DC_Motor_Stop();
		}
		else{/* Nothing */}
	} while(CHOICE_BACK != keypad_pressed_key);

	LCD_voidSendCommand(LCD_CLEAR);
}

void Set_Stepper_Motor_Angle(void)
{
	u16 stepper_motor_angle = 0;
	u8 keypad_pressed_key = 0, cursor_index = 11;

	LCD_voidSendStringPos(1, 1, "Set Angle: ");

	u8 back_flag = 0;

	do
	{
		keypad_voidGetPressedKey(&keypad_pressed_key);

		if('0' <= keypad_pressed_key && '9' >= keypad_pressed_key)
		{
			stepper_motor_angle = (stepper_motor_angle * 10) + (keypad_pressed_key - '0');
			LCD_voidSendCharPos(1, ++cursor_index, keypad_pressed_key);
		}
		else if(SET_ANGLE == keypad_pressed_key)
		{
			LCD_voidSendCommand(LCD_CLEAR);

			LCD_voidSendStringPos(1, 1, "1- Rotate CW");
			LCD_voidSendStringPos(2, 1, "2- Rotate CCW");
			LCD_voidSendStringPos(4, 1, "4- Back");

			do
			{
				keypad_voidGetPressedKey(&keypad_pressed_key);

				if(STEPPER_MOTOR_ROTATE_CW == keypad_pressed_key)
				{
					StepMotor_Set_Angle(stepper_motor_angle, STEP_MOTOR_CW);
				}
				else if(STEPPER_MOTOR_ROTATE_CCW == keypad_pressed_key)
				{
					StepMotor_Set_Angle(stepper_motor_angle, STEP_MOTOR_CCW);
				}
				else{/* Nothing */}

			} while(CHOICE_BACK != keypad_pressed_key);

			back_flag = 1;
		}
		else{/* Nothing */}

	} while(!back_flag);

	LCD_voidSendCommand(LCD_CLEAR);
}
