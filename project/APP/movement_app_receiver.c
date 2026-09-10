/*
 * movement app receiver
 *
 * Created: 9/10/2026
 * Author : Zain
 */
#include <util/delay.h>
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/MotorDriver/motor_driver.h"
#include "../MCAL/UART/UART.h"
#include "../MCAL/Timer1_PWM_ICU/timer1.h"

int main()
{
    u8 receivedCommand = 'S';

    //configure PD4 (OC1B) as output for Timer1 PWM speed control
    DIO_voidSetPinDirection(DPORTD, PIN4, OUTPUT);
    motor_init(DPORTA);
  
    //initialize Timer1 in Fast PWM Mode
    Timer1_ConfigType timer1_config = { TIMER1_F_CPU_8 };
    Timer1_PWM_init(&timer1_config);
   

    //initialize UART at 9600 Baud Rate
    UART_init(9600);

    while (1)
    {
        receivedCommand = UART_receiveByte();
        switch (receivedCommand)
        {
            case 'F':
                motor_moveForward(DPORTA);
                break;
            case 'B':
                motor_moveBackward(DPORTA);
                break;
            case 'R':
                motor_turnRight(DPORTA);
                break;
            case 'L':
                motor_turnLeft(DPORTA);
                break;
            case 'S':
            default:
                motor_stop(DPORTA);
                break;
        }
        _delay_ms(10);
    }
}
