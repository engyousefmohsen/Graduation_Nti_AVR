#include "movement_app.h"

int main()
{
    motor_init(DPORTA);
	DIO_voidSetPinDirection(DPORTD, PIN4, OUTPUT);
	Timer1_ConfigType timer1_config = { TIMER1_F_CPU_8 };
	Timer1_PWM_init(&timer1_config);
	
    while (1) 
    {
		if (DIO_u8ReadPinValue(DPORTA, PIN4) == 0)	
		{
			motor_moveForward(DPORTA);
		} else if (DIO_u8ReadPinValue(DPORTA, PIN5) == 0)
		{
			motor_moveBackward(DPORTA);
		} else if (DIO_u8ReadPinValue(DPORTA, PIN6) == 0)	
		{
			motor_turnRight(DPORTA);
		} else if (DIO_u8ReadPinValue(DPORTA, PIN7) == 0)	
		{
			motor_turnLeft(DPORTA);
		} else {
			motor_stop(DPORTA);
		}
		_delay_ms(10);
    }
}

