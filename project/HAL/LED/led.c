/*
 * led.c
 *
 * HAL Layer - LED / Lamp Driver Implementation
 * Built on top of MCAL/Timer2_PWM (Fast PWM mode).
 */ 

#include "../../LIB/Std_Types.h"
#include "../../MCAL/Timer2_PWM/timer2_pwm.h"

#include "led.h"

void LED_voidInit(void)
{
	TIMER2_voidInit();
}

void LED_voidSetIntensity(u8 Percentage)
{
	u8 OcrValue;

	if(Percentage > 100)
	{
		Percentage = 100;
	}

	/* Map 0-100% to 0-255 (OCR2 range), then hand the raw value to MCAL */
	OcrValue = (u8)(((u16)Percentage * 255) / 100);
	TIMER2_voidSetCompare(OcrValue);
}
