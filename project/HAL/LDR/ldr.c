/*
 * ldr.c
 *Author: Yousef Mohsen
 */ 

#include "../../LIB/Std_Types.h"
#include "../../MCAL/ADC/ADC_int.h"
#include "../../MCAL/DIO/DIO_int.h"

#include "ldr.h"
#include "LDR_config.h"


void LDR_voidInit(void)
{
	/*
	 * DIO_config.h now defaults every port to INPUT (0x00), so PA0 is
	 * already safe. This explicit call is kept for clarity/robustness
	 * in case that default ever changes.
	 */
	DIO_voidSetPinDirection(LDR_PORT, LDR_PIN, INPUT);

	ADC_voidInit();
}

u16 LDR_u16GetRawValue(void)
{
	return ADC_u16Read(LDR_CHANNEL);
}

u8 LDR_u8GetLightPercentage(void)
{
	u16 raw = LDR_u16GetRawValue();
	u8 percentage;

	/* Clamp raw value inside the calibrated range */
	if(raw > LDR_RAW_VALUE_DARK)
	{
		raw = LDR_RAW_VALUE_DARK;
	}
	else if(raw < LDR_RAW_VALUE_BRIGHT)
	{
		raw = LDR_RAW_VALUE_BRIGHT;
	}
	
	/* Linear mapping : BRIGHT -> 100% , DARK -> 0% */
	percentage = (u8)(((u32)(LDR_RAW_VALUE_DARK - raw) * 100)
	                    / (LDR_RAW_VALUE_DARK - LDR_RAW_VALUE_BRIGHT));

	return percentage;
}
