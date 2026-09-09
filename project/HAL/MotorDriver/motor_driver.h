/*
 * motor drive.h
 *
 * Created: 9/8/2026
 * Author : Zain
 */ 

#ifndef MOTORS_H
#define MOTORS_H

#include "../../MCAL/DIO/dio.h"
#include "../../LIB/std_types.h"

//sets the pins needed to control the motors through the motor driver
void motor_init(u8 port);


//is used when needed to stop motors for any reason
void motor_stop(u8 port);

//movement for the car
void motor_moveForward(u8 port);
void motor_moveBackward(u8 port);
void motor_turnRight(u8 port);
void motor_turnLeft(u8 port);

#endif