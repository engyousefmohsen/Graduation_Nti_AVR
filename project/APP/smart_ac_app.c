//Author: Nour amr
#include "../MCAL/DIO/dio.h"
#include "../LIB/std_types.h"
#include "../MCAL/Timer0/TIMER0_int.h"
#include "../MCAL/Timer0/TIMER0_config.h"
#include "../MCAL/Timer0/TIMER0_private.h"
#include "../HAL/LM35/lm35.h"
#include "smart_ac_app.h"
typedef enum { AC_OFF, AC_MEDIUM, AC_HIGH } ac_state_t;
static ac_state_t current_state = AC_OFF;

void SmartAC_voidInit(void) {
    Timer0_voidInit();
    lm35_init();
}

void SmartAC_voidUpdate(void) {
    f32 temp = lm35_read_temp();

    switch (current_state) {
        case AC_OFF:
            if (temp >= TEMP_LOW_ON) current_state = AC_MEDIUM;
            break;
        case AC_MEDIUM:
            if (temp >= TEMP_HIGH_ON) current_state = AC_HIGH;

            else if(temp < TEMP_LOW_OFF)  current_state = AC_OFF;

            break;

        case AC_HIGH:
            if (temp < TEMP_HIGH_OFF) current_state = AC_MEDIUM;
            break;
    }

    u8 duty;
    switch (current_state) {
        case AC_OFF:    duty = FAN_SPEED_OFF;    break;
        case AC_MEDIUM: duty = FAN_SPEED_MEDIUM; break;
        case AC_HIGH:   duty = FAN_SPEED_HIGH;   break;
    }
    Timer0_voidSetPWM(duty);
}
