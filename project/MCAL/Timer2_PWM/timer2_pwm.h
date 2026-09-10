/*
 * timer2_pwm.h
 *
 * MCAL Layer - Timer2 Fast PWM Driver (OC2 / PD7)
 * Same style/logic as the Timer0 PWM driver, just moved to Timer2
 * so it no longer shares OCR0 with Smart AC's fan PWM.
 */

#ifndef TIMER2_PWM_H
#define TIMER2_PWM_H

void TIMER2_voidInit(void);

void TIMER2_voidSetCompare(u8 Copy_u8OCRValue);

void Timer2_voidSetPWM(u8 copy_u8DutyCycle);

#endif
