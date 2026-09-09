/*
 * timer1.h
 *
 * Created: 9/9/2026 12:18:00 AM
 *  Author: Sarah
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "../../LIB/std_types.h"

typedef enum
{
    TIMER1_NO_CLOCK,
    TIMER1_F_CPU_1,
    TIMER1_F_CPU_8,
    TIMER1_F_CPU_64,
    TIMER1_F_CPU_256,
    TIMER1_F_CPU_1024,
    TIMER1_EXTERNAL_FALLING,
    TIMER1_EXTERNAL_RISING
} Timer1_PrescalerType;

typedef enum
{
    TIMER1_ICU_FALLING_EDGE,
    TIMER1_ICU_RISING_EDGE
} Timer1_ICU_EdgeType;



typedef struct
{
    Timer1_PrescalerType prescaler;
} Timer1_ConfigType;


void Timer1_PWM_init(const Timer1_ConfigType *Config_Ptr);

void Timer1_PWM_setDuty(u16 duty);

void Timer1_ICU_init(void);

void Timer1_ICU_setEdge(Timer1_ICU_EdgeType edge);

u16 Timer1_ICU_getCaptureValue(void);

void Timer1_ICU_setCallBack(void (*a_ptr)(void));

void Timer1_ICU_enableInterrupt(void);

void Timer1_ICU_disableInterrupt(void);

void Timer1_deInit(void);

#endif /* TIMER_H_ */