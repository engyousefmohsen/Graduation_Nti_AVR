/*
 * timer1.c
 *
 * Created: 9/9/2026 12:18:00 AM
 *  Author: Sarah
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer1.h"
#include "../../LIB/bit_math.h"


#define TIMER1_PWM_TOP    19999



static volatile void (*g_ICUCallBackPtr)(void) = NULL_PTR;


ISR(TIMER1_CAPT_vect)
{
    if (g_ICUCallBackPtr != NULL_PTR)
    {
        g_ICUCallBackPtr();
    }
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Timer1_PWM_init(const Timer1_ConfigType *Config_Ptr)
{
    /* Clear Timer1 registers */
    TCCR1A = 0;
    TCCR1B = 0;

    /*
     * Fast PWM Mode 15
     *
     * WGM13 = 1
     * WGM12 = 1
     * WGM11 = 1
     * WGM10 = 1
     *
     * OCR1A = TOP
     */
    SET_BIT(TCCR1A, WGM10);
    SET_BIT(TCCR1A, WGM11);

    SET_BIT(TCCR1B, WGM12);
    SET_BIT(TCCR1B, WGM13);

    /*
     * Non-inverting PWM on OC1B
     */
    SET_BIT(TCCR1A, COM1B1);
    CLR_BIT(TCCR1A, COM1B0);

    /*
     * Set PWM TOP
     */
    OCR1A = TIMER1_PWM_TOP;

    /*
     * Start Timer1
     */
    TCCR1B = (TCCR1B & 0xF8) |
             (Config_Ptr->prescaler & 0x07);
}


void Timer1_PWM_setDuty(u16 duty)
{
    OCR1B = duty;
}


void Timer1_ICU_init(void)
{
    /*
     * Start with rising edge detection
     */
    SET_BIT(TCCR1B, ICES1);

    /*
     * Enable Input Capture interrupt
     */
    SET_BIT(TIMSK, TICIE1);
}


void Timer1_ICU_setEdge(Timer1_ICU_EdgeType edge)
{
    if (edge == TIMER1_ICU_RISING_EDGE)
    {
        SET_BIT(TCCR1B, ICES1);
    }
    else
    {
        CLR_BIT(TCCR1B, ICES1);
    }
}


u16 Timer1_ICU_getCaptureValue(void)
{
    return ICR1;
}


void Timer1_ICU_setCallBack(void (*a_ptr)(void))
{
    g_ICUCallBackPtr = a_ptr;
}


void Timer1_ICU_enableInterrupt(void)
{
    SET_BIT(TIMSK, TICIE1);
}


void Timer1_ICU_disableInterrupt(void)
{
    CLR_BIT(TIMSK, TICIE1);
}


void Timer1_deInit(void)
{
    CLR_BIT(TIMSK, TICIE1);

    TCCR1A = 0;
    TCCR1B = 0;

    TCNT1 = 0;
    OCR1A = 0;
    OCR1B = 0;
    ICR1 = 0;

    g_ICUCallBackPtr = NULL_PTR;
}