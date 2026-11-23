#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
//TIM1 已被电机 PWM 占用，控制定时中断改用 TIM2
void Timer_Init(u16 arr,u16 psc);
#endif

