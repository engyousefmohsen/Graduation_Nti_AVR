#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"

#include "../DIO/DIO_int.h"

#include "timer2_pwm.h"

/* Timer2 Registers (ATmega32) */
#define TCCR2   *((volatile u8*)0x45)
#define TCNT2   *((volatile u8*)0x44)
#define OCR2    *((volatile u8*)0x43)

void TIMER2_voidInit(void)
{
    /* OC2 (PD7) must be an output pin to see the PWM waveform */
    DIO_voidSetPinDirection(DPORTD, PIN7, OUTPUT);

    /* Fast PWM mode : WGM21 = 1 , WGM20 = 1 */
    SET_BIT(TCCR2, 6);   /* WGM20 */
    SET_BIT(TCCR2, 3);   /* WGM21 */

    /* Fast PWM, non-inverting mode:
     * COM21 = 1, COM20 = 0
     * OC2 is cleared on compare match and set at BOTTOM.
     * Higher OCR2 value -> higher duty cycle.
     */
    SET_BIT(TCCR2, 5);   /* COM21 */
    CLR_BIT(TCCR2, 4);   /* COM20 */

    /* Start with 0% duty cycle */
    OCR2 = 0;

    /* Prescaler = 64 (CS22:CS20 = 100)
     * Same PWM frequency family as Timer0 (~488Hz @ 8MHz, flicker-free)
     */
    SET_BIT(TCCR2, 2);   /* CS22 */
    CLR_BIT(TCCR2, 1);   /* CS21 */
    CLR_BIT(TCCR2, 0);   /* CS20 */
}

void TIMER2_voidSetCompare(u8 Val)
{
    OCR2 = Val;
}

void Timer2_voidSetPWM(u8 copy_u8DutyCycle)
{
    /* Fast PWM Calculation: Compare Value = (Duty * 255) / 100 */
    u8 local_u8CompareValue = (u16)(copy_u8DutyCycle * 255) / 100;
    TIMER2_voidSetCompare(local_u8CompareValue);
}
