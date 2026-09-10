/*
 * keypad.h
 * Author: Abdelrahman Elbokhary
 * Description: Header file for 4x4 Keypad Driver
 */ 

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../LIB/std_types.h"

/* Keypad Port Configuration on PORTC */
#define KEYPAD_PORT_DIR   DDRC
#define KEYPAD_PORT_OUT   PORTC
#define KEYPAD_PORT_IN    PINC

#define KEYPAD_NOT_PRESSED 0xFF

/* Functions Prototypes */
void Keypad_Init(void);
u8 Keypad_GetPressedKey(void);

#endif /* KEYPAD_H_ */
