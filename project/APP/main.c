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
#include "../MCAL/DIO/DIO_private.h"
#include "../MCAL/DIO/DIO_config.h"

/* Apps Headers */
#include "headlights_app.h"
#include "smart_ac_app.h"
#include "garage_app.h"
#include "movement_app.h" /* ????? ???? ?????? */

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

    /* Movement & Motor Initialization */
    motor_init(DPORTA);
    DIO_voidSetPinDirection(DPORTD, PIN4, OUTPUT);
    Timer1_ConfigType timer1_config = { TIMER1_F_CPU_8 };
    Timer1_PWM_init(&timer1_config);

    /* Enable Global Interrupts for Timer1 ICU */
    SET_BIT(SREG, I);

    while (1)
    {
        /* Movement Control */
        if (DIO_u8ReadPinValue(DPORTA, PIN4) == 0)    
        {
            motor_moveForward(DPORTA);
        } else if (DIO_u8ReadPinValue(DPORTA, PIN5) == 0)
        {
            motor_moveBackward(DPORTA);
        } else if (DIO_u8ReadPinValue(DPORTA, PIN6) == 0)    
        {
            motor_turnRight(DPORTA);
        } else if (DIO_u8ReadPinValue(DPORTA, PIN7) == 0)    
        {
            motor_turnLeft(DPORTA);
        } else {
            motor_stop(DPORTA);
        }

        /* Smart AC */
        SmartAC_voidUpdate();

        /* Headlights */
        HEADLIGHTS_voidMainFunction();

        /* Garage */
        Garage_update();

        /* Delay between application updates */
        _delay_ms(10); /* ?? ??????? ?? 10ms ????????? ??????? ?????? ?????? */
    }

    return 0;
}