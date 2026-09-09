/*
 * headlights_app.c
 *
 * APP Layer - Automatic Headlight Intensity Control
 *
 * Logic:
 *   1) Read ambient light percentage from the LDR (0 = dark, 100 = bright)
 *   2) Convert it to the required lamp intensity (inverse relation :
 *      the darker the street, the higher the lamp intensity)
 *   3) Apply hysteresis so small fluctuations around a threshold don't
 *      make the lamp flicker
 *   4) Drive the lamp intensity through the LED HAL driver
 */ 

#include "../LIB/Std_Types.h"
#include "../HAL/LDR/ldr.h"
#include "../HAL/LED/led.h"

#include "headlights_app.h"
#include "headlights_config.h"



/* Invalid initial value -> forces the very first reading to be applied */
static u8 LastLightPercentage = 0xFF;

void HEADLIGHTS_voidInit(void)
{
	LDR_voidInit();
	LED_voidInit();

	/* Lamp OFF until the first reading is taken */
	LED_voidSetIntensity(0);
}

void HEADLIGHTS_voidMainFunction(void)
{
	u8  lightPercentage;
	u8  lampIntensity;
	s16 diff; //difference between the last light percentage and the current one

	/* 1) Read the current ambient light level */
	lightPercentage = LDR_u8GetLightPercentage();

	/* Hysteresis check */
	diff = (s16)lightPercentage - (s16)LastLightPercentage;
	if(diff < 0)
	{
		diff = -diff;
	}
	else
	{
		
	}

	if((LastLightPercentage == 0xFF) || (diff > HEADLIGHTS_HYSTERESIS_MARGIN))
	{
		/* 2) Inverse mapping : darker street -> higher lamp intensity */
		lampIntensity = 100 - lightPercentage;

		/* 3) Drive the lamp */
		LED_voidSetIntensity(lampIntensity);

		/* 4) Remember the last acted-upon value */
		LastLightPercentage = lightPercentage;
	}
	else
	{
		
	}
}
