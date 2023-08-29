/*****************************************************
************    Author: Ehab Magdy		**************
************	SWC	  : dc_motor.h		**************
************	Data  : 28 Aug, 2023	**************
******************************************************/

/********************  Includes **********************/
#include "../../Library/STD_Types.h"

/************** Macro definitions ********************/
#define DC_MOTOR_PORT       DIO_PORTB

#define DC_MOTOR_PIN_0      DIO_PIN6
#define DC_MOTOR_PIN_1      DIO_PIN7

/************** Functions Decelerations **************/
void DC_Motor_Initiliaze();
void DC_Motor_Move_CW();
void DC_Motor_Move_CCW();
void DC_Motor_Stop();
