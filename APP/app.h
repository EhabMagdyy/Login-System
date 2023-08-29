/*****************************************************
************    Author: Ehab Magdy		**************
************	SWC	  : app.h			**************
************	Data  : 28 Aug, 2023	**************
******************************************************/

#ifndef APP_H
#define APP_H

/********************  Includes **********************/
#include <math.h>
#include "util/delay.h"
#include "../MCAL/DIO/dio.h"
#include "../HAL/LCD/lcd.h"
#include "../HAL/Keypad/keypad.h"
#include "../HAL/Stepper_Motor/stepper_motor.h"
#include "../HAL/DC_Motor/dc_motor.h"
#include "../MCAL/ADC/adc.h"

/************** Macro definitions ********************/
#define LOGIN_DENIED			  0
#define LOGIN_SUCCESSFULLY		  1

#define CHIOCE_TEMPERATURE		 '1'
#define CHIOCE_STEPPER_MOTOR	 '2'
#define CHIOCE_DC_MOTOR 		 '3'
#define CHIOCE_CLOSE			 '4'

#define SET_ANGLE				 '#'

#define DC_MOTOR_ROTATE_CW		 '1'
#define DC_MOTOR_ROTATE_CCW		 '2'
#define DC_MOTOR_STOP			 '3'

#define STEPPER_MOTOR_ROTATE_CW  '1'
#define STEPPER_MOTOR_ROTATE_CCW '2'

#define CHOICE_BACK				 '4'

/************** Functions Decelerations **************/
u8 login_system(void);
void Read_Temp(void);
void Set_DC_Motor_Direction(void);
void Set_Stepper_Motor_Angle(void);

#endif /* APP_H */
