#include "../../LIB/std_types.h"
#include "../../MCAL/DIO/dio.h"
#include "../../MCAL/Timer1_PWM_ICU/timer1.h"
#include "servo.h"

/* OC1B Pin Definition */
#define SERVO_PORT   DPORTD
#define SERVO_PIN    PIN4

void Servo_init(void)
{
    /* Set OC1B Pin as Output */
    DIO_voidSetPinDirection(
        SERVO_PORT,
        SERVO_PIN,
        OUTPUT
    );
}

void Servo_setAngle(u8 Copy_u8Angle)
{
    u16 compareVal;

    /* Limit angle to 180 degrees */
    if(Copy_u8Angle > 180)
    {
        Copy_u8Angle = 180;
    }

    /*
     * Map angle:
     *
     * 0 degree   -> 1000 us
     * 90 degree  -> 1500 us
     * 180 degree -> 2000 us
     *
     * Timer tick = 1 us
     */
    compareVal = 1000 +
                 (((u32)Copy_u8Angle * 1000) / 180);

    Timer1_PWM_setDuty(compareVal);
}