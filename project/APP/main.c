/*
 * main.c
 *
 * Smart Car - Application Entry Point
 */

#define F_CPU 8000000UL

#include <util/delay.h>

#include "../LIB/Std_Types.h"
#include "../LIB/bit_math.h"
#include "../MCAL/DIO/DIO_int.h"

#include "headlights_app.h"
#include "smart_ac_app.h"
#include "garage_app.h"


/* SREG Register */
#define SREG *((volatile u8 *)0x5F)

/* Global Interrupt Enable bit */
#define I 7


int main(void)
{
    /* Initialize DIO */
    DIO_voidInitialization();

    /* Initialize Applications */
    SmartAC_voidInit();
    HEADLIGHTS_voidInit();
    Garage_init();

    /* Enable Global Interrupts for Timer1 ICU */
    SET_BIT(SREG, I);

    while (1)
    {
        /* Smart AC */
        SmartAC_voidUpdate();

        /* Headlights */
        HEADLIGHTS_voidMainFunction();

        /* Garage */
        Garage_update();

        /* Delay between application updates */
        _delay_ms(100);
    }

    return 0;
}
