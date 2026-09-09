/*
 * ultrasonic.c
 *
 * Created: 9/8/2026  9:20:45 AM
 * Author: Sarah
 */

#include <util/delay.h>

#include "../../LIB/std_types.h"
#include "../../LIB/bit_math.h"
#include "../../MCAL/DIO/dio.h"
#include "../../MCAL/Timer1_PWM_ICU/timer1.h"
#include "ultrasonic.h"

//global variables 

static volatile u16 g_pulseTime = 0;
static volatile u8 g_edgeCounter = 0;
static volatile u8 g_measurementDone = 0;



void Ultrasonic_init(void)
{
    /* Setup Trigger Pin Direction as Output */
    DIO_voidSetPinDirection(
        ULTRASONIC_TRIGGER_PORT,
        ULTRASONIC_TRIGGER_PIN,
        OUTPUT
    );

    /* Initial Trigger state = LOW */
    DIO_voidSetPinValue(
        ULTRASONIC_TRIGGER_PORT,
        ULTRASONIC_TRIGGER_PIN,
        LOW
    );

    /* Initialize ICU */
    Timer1_ICU_init();

    /* Set ICU callback */
    Timer1_ICU_setCallBack(Ultrasonic_edgeProcessing);
}


void Ultrasonic_Trigger(void)
{
    /* Send 10 us trigger pulse */

    DIO_voidSetPinValue(
        ULTRASONIC_TRIGGER_PORT,
        ULTRASONIC_TRIGGER_PIN,
        HIGH
    );

    _delay_us(10);

    DIO_voidSetPinValue(
        ULTRASONIC_TRIGGER_PORT,
        ULTRASONIC_TRIGGER_PIN,
        LOW
    );
}


u16 Ultrasonic_readDistance(void)
{
    u16 distance = 0;

    /* Prepare for a new measurement */
    g_measurementDone = 0;
    g_edgeCounter = 0;
    g_pulseTime = 0;

    /* Send trigger pulse */
    Ultrasonic_Trigger();

    /* Wait until rising + falling edges are captured */
    while(g_measurementDone == 0)
    {
        /* Waiting for ICU interrupt */
    }

    /*
     * Convert echo pulse time in microseconds
     * to distance in centimeters.
     *
     * Distance = Time / 58
     */
    distance = (u16)(g_pulseTime / 58);

    return distance;
}


void Ultrasonic_edgeProcessing(void)
{
    static u16 t1 = 0;
    static u16 t2 = 0;

    g_edgeCounter++;

    if(g_edgeCounter == 1)
    {
        /* Rising edge: start of Echo pulse */

        t1 = Timer1_ICU_getCaptureValue();

        /* Change ICU to falling edge */
        Timer1_ICU_setEdge(TIMER1_ICU_FALLING_EDGE);
    }
    else if(g_edgeCounter == 2)
    {
        /* Falling edge: end of Echo pulse */

        t2 = Timer1_ICU_getCaptureValue();

        /*
         * Timer1 TOP = 19999
         * Therefore the timer counts from 0 to 19999
         * and repeats every 20000 us.
         */

        if(t2 >= t1)
        {
            g_pulseTime = t2 - t1;
        }
        else
        {
            /* Timer1 wrapped around */
            g_pulseTime = (20000 - t1) + t2;
        }

        /* Prepare ICU for next measurement */
        Timer1_ICU_setEdge(TIMER1_ICU_RISING_EDGE);

        g_edgeCounter = 0;

        /* Measurement completed */
        g_measurementDone = 1;
    }
}