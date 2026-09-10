/*
 * garage_app.c
 *
 * Created: 9/8/2026
 * Author: Sarah
 *
 * Owns Timer1 exclusively:
 *   - PWM on OC1B  -> drives the Servo (door actuator)
 *   - Input Capture (ICR1) -> measures the Ultrasonic echo pulse
 *
 * Fast PWM Mode 15 (used in Timer1_PWM_init) uses OCR1A only as the
 * PWM TOP value, which leaves ICR1 free for the Input Capture Unit.
 * That is what lets the PWM (servo) and ICU (ultrasonic) share Timer1
 * safely at the same time.
 */

#include "../LIB/std_types.h"
#include "../MCAL/Timer1_PWM_ICU/timer1.h"
#include "../HAL/Ultrasonic/ultrasonic.h"
#include "../HAL/Servo/servo.h"
#include "garage_app.h"

// global variables

static Garage_StateType g_state = GARAGE_STATE_CLOSED;
static u8 g_confirmCounter = 0;

// functions definitions 

void Garage_init(void)
{
    Timer1_ConfigType Timer1_Config = { TIMER1_F_CPU_8 };

    /* Configure Timer1 PWM (drives the Servo on OC1B) */
    Timer1_PWM_init(&Timer1_Config);

    /* Configure Ultrasonic (uses Timer1 ICU internally) */
    Ultrasonic_init();

    /* Configure Servo pin */
    Servo_init();

    /* Start with the door closed */
    Servo_setAngle(GARAGE_CLOSED_ANGLE);
    g_state = GARAGE_STATE_CLOSED;
    g_confirmCounter = 0;
}


void Garage_update(void)
{
    u16 distance = Ultrasonic_readDistance();

    switch(g_state)
    {
        case GARAGE_STATE_CLOSED:

            if(distance <= GARAGE_DETECT_DISTANCE_CM)
            {
                g_confirmCounter++;

                if(g_confirmCounter >= GARAGE_CONFIRM_COUNT)
                {
                    Servo_setAngle(GARAGE_OPEN_ANGLE);
                    g_state = GARAGE_STATE_OPEN;
                    g_confirmCounter = 0;
                }
            }
            else
            {
                /* Reading didn't confirm approach; reset the counter */
                g_confirmCounter = 0;
            }
            break;

        case GARAGE_STATE_OPEN:

            if(distance >= GARAGE_CLEAR_DISTANCE_CM)
            {
                g_confirmCounter++;

                if(g_confirmCounter >= GARAGE_CONFIRM_COUNT)
                {
                    Servo_setAngle(GARAGE_CLOSED_ANGLE);
                    g_state = GARAGE_STATE_CLOSED;
                    g_confirmCounter = 0;
                }
            }
            else
            {
                /* Car still within range; reset the counter */
                g_confirmCounter = 0;
            }
            break;

        default:
            break;
    }
}

Garage_StateType Garage_getState(void)
{
    return g_state;
}