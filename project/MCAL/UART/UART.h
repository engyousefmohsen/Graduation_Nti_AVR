/*
 * uart.h
 *
 * Created: 9/10/2026
 * Author : Zain
 */

#ifndef UART_H_
#define UART_H_

#include "../../LIB/std_types.h"

// UART Register Addresses for ATmega32
#define UDR       *((volatile u8*)0x2C)
#define UCSRA     *((volatile u8*)0x2B)
#define UCSRB     *((volatile u8*)0x2A)
#define UCSRC     *((volatile u8*)0x40)
#define UBRRH     *((volatile u8*)0x40)
#define UBRRL     *((volatile u8*)0x29)

// Register Bit Definitions 
#define RXC       7
#define TXC       6
#define UDRE      5
#define U2X       1

#define RXEN      4
#define TXEN      3

#define URSEL     7
#define UCSZ1     2
#define UCSZ0     1

// Initializes the UART module with a given baud rate (e.g., 9600)
void UART_init(u32 baud_rate);

//Transmits a single byte over UART (TX pin)
void UART_sendByte(u8 data);

//Receives a single byte over UART (RX pin) - Blocking call
u8 UART_receiveByte();

#endif
