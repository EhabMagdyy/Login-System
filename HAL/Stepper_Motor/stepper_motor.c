/*****************************************************
************    Author: Ehab Magdy		**************
************	SWC	  : stepper_motor.c **************
************	Data  : 28 Aug, 2023	**************
******************************************************/

#include <avr/io.h>
#include "../../MCAL/DIO/dio.h"
#include "stepper_motor.h"
#include "util/delay.h"

void StepMotor_Init(void)
{
    DIO_voidSetPinDirection(STEP_MOTOR_PORT, STEP_MOTOR_BLUE, DIO_DIRECTION_OUTPUT);
    DIO_voidSetPinDirection(STEP_MOTOR_PORT, STEP_MOTOR_PINK, DIO_DIRECTION_OUTPUT);
    DIO_voidSetPinDirection(STEP_MOTOR_PORT, STEP_MOTOR_YELLOW, DIO_DIRECTION_OUTPUT);
    DIO_voidSetPinDirection(STEP_MOTOR_PORT, STEP_MOTOR_ORANGE, DIO_DIRECTION_OUTPUT);

    DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_BLUE, DIO_LOW);
    DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_PINK, DIO_LOW);
    DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_YELLOW, DIO_LOW);
    DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_ORANGE, DIO_LOW);
}

void StepMotor_Set_Angle(u16 angle, u8 direction)
{
	/* this may be not the best way! */

    if(360 >= angle)
    {
        u16 num_of_4steps = (angle / STEP_ANGLE) / 4;

        if(STEP_MOTOR_CW == direction)
        {
			for(u16 steps_itertion = 0 ; steps_itertion < num_of_4steps ; steps_itertion++)
			{
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_BLUE, DIO_HIGH);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_PINK, DIO_LOW);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_YELLOW, DIO_LOW);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_ORANGE, DIO_LOW);
				_delay_ms(STEP_TIME);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_BLUE, DIO_LOW);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_PINK, DIO_HIGH);
				_delay_ms(STEP_TIME);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_PINK, DIO_LOW);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_YELLOW, DIO_HIGH);
				_delay_ms(STEP_TIME);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_YELLOW, DIO_LOW);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_ORANGE, DIO_HIGH);
				_delay_ms(STEP_TIME);
			}
        }
        else if(STEP_MOTOR_CCW == direction)
        {
			for(u16 steps_itertion = 0 ; steps_itertion < num_of_4steps ; steps_itertion++)
			{
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_ORANGE, DIO_HIGH);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_YELLOW, DIO_LOW);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_PINK, DIO_LOW);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_BLUE, DIO_LOW);
				_delay_ms(STEP_TIME);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_ORANGE, DIO_LOW);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_YELLOW, DIO_HIGH);
				_delay_ms(STEP_TIME);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_YELLOW, DIO_LOW);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_PINK, DIO_HIGH);
				_delay_ms(STEP_TIME);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_PINK, DIO_LOW);
				DIO_voidSetPinValue(STEP_MOTOR_PORT, STEP_MOTOR_BLUE, DIO_HIGH);
				_delay_ms(STEP_TIME);
			}
        }
    }
    else{/* Nothing */}
}
