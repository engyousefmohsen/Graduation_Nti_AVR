#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"

#include "../DIO/DIO_int.h"

#include "ADC_int.h"
#include "ADC_config.h"
#include "ADC_private.h"

void ADC_voidInit(void)
{
    /* AVCC as voltage reference */
    CLR_BIT(ADMUX, REFS1);
    SET_BIT(ADMUX, REFS0);

    /* Right adjustment */
    CLR_BIT(ADMUX, ADLAR);

    /* ADC Prescaler = 64 */
    SET_BIT	(ADCSRA, ADPS2);
    SET_BIT	(ADCSRA, ADPS1);
    CLR_BIT(ADCSRA, ADPS0);

    /* Enable ADC */
    SET_BIT(ADCSRA, ADEN);
}

u16 ADC_u16Read(u8 Channel)
{
    ADMUX &= 0xE0;

    ADMUX |= (Channel & 0x07);

    SET_BIT(ADCSRA, ADSC);

    while (GET_BIT(ADCSRA, ADSC) == 1);

    u16 low_byte = ADCL;
    u16 high_byte = ADCH;
    u16 final_result = low_byte | (high_byte << 8);

    return final_result;
}
