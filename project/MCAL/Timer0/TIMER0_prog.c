#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"

#include "../DIO/DIO_int.h"

#include "TIMER0_int.h"
#include "TIMER0_config.h"
#include "TIMER0_private.h"

void TIMER0_voidInit(void)
{
    if(TIMER0_MODE==CTC)
    {
        Set_Bit(TCCR0, 3);
        Clear_Bit(TCCR0, 6);

        Set_Bit(TIMSK, 1);
        Set_Bit(TCCR0, 0);
        Clear_Bit(TCCR0, 1);
        Set_Bit(TCCR0, 2);
    }
    else if(TIMER0_MODE==PWM)
    {
        /* OC0 (PB3) must be an output pin to see the PWM waveform */
        DIO_voidSetPinDirection(DPORTB, PIN3, OUTPUT);

        /* Fast PWM mode : WGM01 = 1 , WGM00 = 1 */
        Set_Bit(TCCR0, 6);   /* WGM00 */
        Set_Bit(TCCR0, 3);   /* WGM01 */

        /* Non-inverting mode : COM01 = 1 , COM00 = 0
         * -> OC0 cleared on compare match, set at TOP (higher OCR0 = more ON time) */
        Set_Bit(TCCR0, 5);   /* COM01 */
        Clear_Bit(TCCR0, 4); /* COM00 */

        /* Start with 0% duty cycle */
        OCR0 = 0;

        /* Prescaler selection (CS02:CS00), from TIMER0_config.h */
        #if (PRESCALER == DIV_1)
            Set_Bit(TCCR0, 0);   Clear_Bit(TCCR0, 1); Clear_Bit(TCCR0, 2);
        #elif (PRESCALER == DIV_8)
            Clear_Bit(TCCR0, 0); Set_Bit(TCCR0, 1);   Clear_Bit(TCCR0, 2);
        #elif (PRESCALER == DIV_64)
            Set_Bit(TCCR0, 0);   Set_Bit(TCCR0, 1);   Clear_Bit(TCCR0, 2);
        #elif (PRESCALER == DIV_256)
            Clear_Bit(TCCR0, 0); Clear_Bit(TCCR0, 1); Set_Bit(TCCR0, 2);
        #elif (PRESCALER == DIV_1024)
            Set_Bit(TCCR0, 0);   Clear_Bit(TCCR0, 1); Set_Bit(TCCR0, 2);
        #endif
    }
    else
    {
        Clear_Bit(TCCR0, 3);
        Clear_Bit(TCCR0, 6);
    }

}

void TIMER0_voidDelay1Sec(void)
{

    Set_Bit(TCCR0, 0);
    Clear_Bit(TCCR0, 1);
    Set_Bit(TCCR0, 2);

    for(u8 count = 0; count < 50; count++)
    {
        TCNT0 = 256-156;

        while(Get_Bit(TIFR, 0) == 0);
        Set_Bit(TIFR, 0);
    }

    TCCR0 &= 0xF8;
}

void TIMER0_voidSetCompare(u8 Val)
{
    OCR0 = Val;
}
