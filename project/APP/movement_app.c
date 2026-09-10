#include "movement_app.h"
//transmitter

int main(void)
{
    /* Initialize DIO */
    DIO_voidInitialization();

    /* Movement & Motor Initialization */
    motor_init(DPORTA);
    Timer1_ConfigType timer1_config = { TIMER1_F_CPU_8 };
    Timer1_PWM_init(&timer1_config);

    while (1)
    {
        /* Movement Control */
        if (DIO_u8ReadPinValue(DPORTA, PIN4) == 0)    
        {
            UART_sendByte('F');
        } else if (DIO_u8ReadPinValue(DPORTA, PIN5) == 0)
        {
            UART_sendByte('B');
        } else if (DIO_u8ReadPinValue(DPORTA, PIN6) == 0)    
        {
            UART_sendByte('R');
        } else if (DIO_u8ReadPinValue(DPORTA, PIN7) == 0)    
        {
            UART_sendByte('L');
        } else {
            UART_sendByte('S');
        }
        _delay_ms(10);
    }
}
