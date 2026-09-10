/*
 * garage_app.h
 *
 * Created: 9/8/2026
 * Author: Sarah
 * Description: Garage door control - combines Ultrasonic (Timer1 ICU)
 *              and Servo (Timer1 PWM/OC1B) into a debounced,
 *              hysteresis-based state machine so the door does not
 *              flicker open/closed near the detection threshold.
 *
 * NOTE: This module owns Timer1 entirely (both ICU and PWM). No other
 *       module should call Timer1_PWM_init / Timer1_ICU_init directly.
 */

#ifndef GARAGE_APP_H_
#define GARAGE_APP_H_

#include "../LIB/std_types.h"



/* Distance (cm) at which an approaching car is considered "detected" */
#define GARAGE_DETECT_DISTANCE_CM   20

/* Distance (cm) at which the car is considered "clear" of the door.*/
#define GARAGE_CLEAR_DISTANCE_CM    30


#define GARAGE_CONFIRM_COUNT        3

/* Servo angles representing the two door positions */
#define GARAGE_CLOSED_ANGLE         0
#define GARAGE_OPEN_ANGLE           90



typedef enum
{
    GARAGE_STATE_CLOSED,
    GARAGE_STATE_OPEN
} Garage_StateType;



/* Initializes Timer1 (PWM + ICU), Ultrasonic, and Servo. Door starts closed. */
void Garage_init(void);


void Garage_update(void);

/* Returns the current confirmed door state */
Garage_StateType Garage_getState(void);

#endif /* GARAGE_APP_H_ */