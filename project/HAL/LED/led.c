/*
 * led.c
 *
 * HAL Layer - LED / Lamp Driver Implementation
 * Built on top of MCAL/Timer0 (Fast PWM mode).
 */ 

#include "../../LIB/Std_Types.h"
#include "../../MCAL/Timer0/TIMER0_int.h"

#include "led.h"

void LED_voidInit(void)
{
	TIMER0_voidInit();
}

void LED_voidSetIntensity(u8 Percentage)
{
	u8 OcrValue;

	if(Percentage > 100)
	{
		Percentage = 100;
	}

	/* Map 0-100% to 0-255 (OCR0 range), then hand the raw value to MCAL */
	OcrValue = (u8)(((u16)Percentage * 255) / 100);
	TIMER0_voidSetCompare(OcrValue);
}
