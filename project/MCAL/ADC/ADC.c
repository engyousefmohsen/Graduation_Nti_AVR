#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"

#include "../DIO/DIO_int.h"

#include "ADC_int.h"
#include "ADC_config.h"
#include "ADC_private.h"

void ADC_voidInit(void)
{
    /* AVCC as voltage reference */
    Clear_Bit(ADMUX, REFS1);
    Set_Bit(ADMUX, REFS0);

    /* Right adjustment */
    Clear_Bit(ADMUX, ADLAR);

    /* ADC Prescaler = 64 */
    Set_Bit(ADCSRA, ADPS2);
    Set_Bit(ADCSRA, ADPS1);
    Clear_Bit(ADCSRA, ADPS0);

    /* Enable ADC */
    Set_Bit(ADCSRA, ADEN);
}

u16 ADC_u16Read(u8 Channel)
{
    ADMUX &= 0xE0;

    ADMUX |= (Channel & 0x07);

    Set_Bit(ADCSRA, ADSC);

    while (Get_Bit(ADCSRA, ADSC) == 1);

    u16 low_byte = ADCL;
    u16 high_byte = ADCH;
    u16 final_result = low_byte | (high_byte << 8);

    return final_result;
}
