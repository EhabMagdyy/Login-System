/*****************************************************
************    Author: Ehab Magdy		**************
************	SWC	  : dc_motor.c		**************
************	Data  : 28 Aug, 2023	**************
******************************************************/

#include <avr/io.h>
#include "../../MCAL/DIO/dio.h"
#include "dc_motor.h"

void DC_Motor_Initiliaze()
{
    DIO_voidSetPinDirection(DC_MOTOR_PORT, DC_MOTOR_PIN_0, DIO_DIRECTION_OUTPUT);
    DIO_voidSetPinDirection(DC_MOTOR_PORT, DC_MOTOR_PIN_1, DIO_DIRECTION_OUTPUT);

    DIO_voidSetPinValue(DC_MOTOR_PORT, DC_MOTOR_PIN_0, DIO_LOW);
    DIO_voidSetPinValue(DC_MOTOR_PORT, DC_MOTOR_PIN_1, DIO_LOW);
}

void DC_Motor_Move_CW()
{
    DIO_voidSetPinValue(DC_MOTOR_PORT, DC_MOTOR_PIN_0, DIO_HIGH);
    DIO_voidSetPinValue(DC_MOTOR_PORT, DC_MOTOR_PIN_1, DIO_LOW);
}

void DC_Motor_Move_CCW()
{
    DIO_voidSetPinValue(DC_MOTOR_PORT, DC_MOTOR_PIN_0, DIO_LOW);
    DIO_voidSetPinValue(DC_MOTOR_PORT, DC_MOTOR_PIN_1, DIO_HIGH);
}

void DC_Motor_Stop()
{
    DIO_voidSetPinValue(DC_MOTOR_PORT, DC_MOTOR_PIN_0, DIO_LOW);
    DIO_voidSetPinValue(DC_MOTOR_PORT, DC_MOTOR_PIN_1, DIO_LOW);
}
