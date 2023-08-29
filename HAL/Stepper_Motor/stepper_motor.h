/*****************************************************
************    Author: Ehab Magdy		**************
************	SWC	  : stepper_motor.h **************
************	Data  : 28 Aug, 2023	**************
******************************************************/

#ifndef STEPPER_MOTOR_H
#define	STEPPER_MOTOR_H

/********************  Includes **********************/
#include "../../Library/STD_Types.h"

/************** Macro definitions ********************/
#define STEP_MOTOR_PORT      DIO_PORTB

#define STEP_MOTOR_BLUE      DIO_PIN0
#define STEP_MOTOR_PINK      DIO_PIN1
#define STEP_MOTOR_YELLOW    DIO_PIN2
#define STEP_MOTOR_ORANGE    DIO_PIN3

#define STEP_ANGLE            0.1f

#define STEP_MOTOR_CW            1
#define STEP_MOTOR_CCW           0

#define STEP_TIME	10

/************** Functions Decelerations **************/
void StepMotor_Init(void);
void StepMotor_Set_Angle(u16 angle, u8 direction);

#endif	/* STEPPER_MOTOR_H */

