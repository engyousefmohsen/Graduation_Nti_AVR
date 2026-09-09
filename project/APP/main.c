/*
 * main.c
 *
 * Smart Car - Application Entry Point
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>

#include "../LIB/Std_Types.h"
#include "../MCAL/DIO/DIO_int.h"
#include "headlights_app.h"
#include "smart_ac_app.h"

/* TODO (team): call the Init/MainFunction of garage_app, movement_app,
 * and smart_ac_app here as well once each teammate finishes their part. */

int main(void)
{
	DIO_voidInitialization();
    SmartAC_voidInit();
	HEADLIGHTS_voidInit();

	while(1)
	{
		SmartAC_voidUpdate();

		HEADLIGHTS_voidMainFunction();
		_delay_ms(100);
	}

	return 0;
}
