/*
 * uart.c
 *
 * Created: 9/10/2026
 * Author : Zain
 */

#include "UART.h"
#include "../DIO/DIO_int.h"
#include "../../LIB/bit_math.h"
#include "../../LIB/std_types.h"

void UART_init(u32 baud_rate)
{
    u16 ubrr_value = 0;

    //UART pins
    DIO_voidSetPinDirection(DPORTD, PIN0, INPUT);
    DIO_voidSetPinDirection(DPORTD, PIN1, OUTPUT);

    SET_BIT(UCSRA, U2X);
    SET_BIT(UCSRB, RXEN);
    SET_BIT(UCSRB, TXEN);

    //data bits:8, stop bit:1, paratiy:-
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);

    ubrr_value = (u16)(((F_CPU / (8UL * baud_rate))) - 1);

    UBRRH = (u8)(ubrr_value >> 8);
    UBRRL = (u8)(ubrr_value);
}

void UART_sendByte(u8 data)
{
    //waits for the UDRE flag to be empty
    while (GET_BIT(UCSRA, UDRE) == 0);

    //send data
    UDR = data;
}

u8 UART_receiveByte()
{
    //waits till RXC flag is set
    while (GET_BIT(UCSRA, RXC) == 0);

    //read and return data
    return UDR;
}
