/*
 * uart.h
 *
 * Created: 9/10/2026
 * Author : Zain
 */

#ifndef UART_H_
#define UART_H_

#include "../../LIB/std_types.h"

// Initializes the UART module with a given baud rate (e.g., 9600)
void UART_init(u32 baud_rate);

//Transmits a single byte over UART (TX pin)
void UART_sendByte(u8 data);

//Receives a single byte over UART (RX pin) - Blocking call
u8 UART_receiveByte();

#endif
