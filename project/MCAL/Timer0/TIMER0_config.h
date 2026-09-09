#ifndef TIMER0_CONFIG_H
#define TIMER0_CONFIG_H

/* Modes supported by TIMER0_voidInit() */
#define CTC 0
#define PWM 1   /* <-- Added: not present in the original template,
                       needed to control the headlight lamp brightness */

#define TIMER0_MODE PWM

/* Prescaler options (used only by the PWM branch) - CS02:CS00 */
#define DIV_1      0
#define DIV_8      1
#define DIV_64     2
#define DIV_256    3
#define DIV_1024   4

/* F_CPU = 8MHz, Prescaler = 64 -> PWM freq ~= 488Hz (flicker-free for a lamp) */
#define PRESCALER  DIV_64 //the equation to calculate the frequency is F_CPU/(Prescaler*256)

#endif
