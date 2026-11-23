#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
#define PI 3.14159265
#define ZHONGZHI 0
void TIM2_IRQHandler(void) ;
void Set_Pwm(int motor_a,int motor_b);
void Key(void);
void Xianfu_Pwm(void);
u8 Turn_Off( int voltage);
int myabs(int a);
int Incremental_PI_A (int Encoder,int Target);
int Incremental_PI_B (int Encoder,int Target);
void Usart_Control(void);
#endif

