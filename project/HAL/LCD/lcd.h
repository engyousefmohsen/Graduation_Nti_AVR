/*
 * lcd.h
 * Author: Abdelrahman Elbokhary
 * Description: Header file for LCD Driver (4-bit mode) - Split Ports
 */ 

#ifndef LCD_H_
#define LCD_H_

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../LIB/std_types.h"

/* LCD Control Pins (PORTA) */
#define LCD_CTRL_DIR  DDRA
#define LCD_CTRL_PORT PORTA
#define RS_PIN        PA2
#define EN_PIN        PA3

/* LCD Data Pins (PORTD Lower Nibble: PD0, PD1, PD2, PD3) */
#define LCD_DATA_DIR  DDRD
#define LCD_DATA_PORT PORTD

/* LCD Commands */
#define LCD_CLEAR_COMMAND              0x01
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_SET_CURSOR_LOCATION        0x80

/* Functions Prototypes */
void LCD_Init(void);
void LCD_SendCommand(u8 command);
void LCD_WriteChar(u8 data);
void LCD_WriteString(const char *Str);
void LCD_Clear(void);
void LCD_GoToXY(u8 row, u8 col);

#endif /* LCD_H_ */
