/*
 * motor drive.c
 *
 * Created: 9/8/2026
 * Author : Zain
 */ 
#include "motor_driver.h"
#include "../../LIB/std_types.h"

void motor_init(u8 port) 
{
	DIO_voidSetPinDirection(port, PIN0, OUTPUT);
	DIO_voidSetPinDirection(port, PIN1, OUTPUT);
	DIO_voidSetPinDirection(port, PIN2, OUTPUT);
	DIO_voidSetPinDirection(port, PIN3, OUTPUT);
	DIO_voidSetPinDirection(port, PIN4, INPUT);
	DIO_voidSetPinDirection(port, PIN5, INPUT);
	DIO_voidSetPinDirection(port, PIN6, INPUT);
	DIO_voidSetPinDirection(port, PIN7, INPUT);
	
	DIO_voidSetPinValue(port, PIN4, HIGH);
	DIO_voidSetPinValue(port, PIN5, HIGH);
	DIO_voidSetPinValue(port, PIN6, HIGH);
	DIO_voidSetPinValue(port, PIN7, HIGH);
	
	motor_stop(port);
}

void motor_stop(u8 port)
{
	DIO_voidSetPinValue(port, PIN0, LOW);
	DIO_voidSetPinValue(port, PIN1, LOW);
	DIO_voidSetPinValue(port, PIN2, LOW);
	DIO_voidSetPinValue(port, PIN3, LOW);
	
}

void motor_moveForward(u8 port)
{
	DIO_voidSetPinValue(port, PIN0, HIGH);
	DIO_voidSetPinValue(port, PIN1, LOW);
	DIO_voidSetPinValue(port, PIN2, HIGH);
	DIO_voidSetPinValue(port, PIN3, LOW);
}

void motor_moveBackward(u8 port)
{
	DIO_voidSetPinValue(port, PIN0, LOW);
	DIO_voidSetPinValue(port, PIN1, HIGH);
	DIO_voidSetPinValue(port, PIN2, LOW);
	DIO_voidSetPinValue(port, PIN3, HIGH);
}

void motor_turnRight(u8 port)
{
	DIO_voidSetPinValue(port, PIN0, HIGH);
	DIO_voidSetPinValue(port, PIN1, LOW);
	DIO_voidSetPinValue(port, PIN2, LOW);
	DIO_voidSetPinValue(port, PIN3, HIGH);
}

void motor_turnLeft(u8 port)
{
	DIO_voidSetPinValue(port, PIN0, LOW);
	DIO_voidSetPinValue(port, PIN1, HIGH);
	DIO_voidSetPinValue(port, PIN2, HIGH);
	DIO_voidSetPinValue(port, PIN3, LOW);
}