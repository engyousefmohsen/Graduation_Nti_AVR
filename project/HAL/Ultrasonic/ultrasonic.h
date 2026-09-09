/*
 * ultrasonic.c
 *
 * Created: 9/8/2026  9:20:40 AM
 * Author: Sarah
 */


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "../../LIB/std_types.h"
#include "../../MCAL/DIO/dio.h"

/* Trigger Pin Definition */
#define ULTRASONIC_TRIGGER_PORT   DPORTB
#define ULTRASONIC_TRIGGER_PIN    PIN0

void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
u16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */