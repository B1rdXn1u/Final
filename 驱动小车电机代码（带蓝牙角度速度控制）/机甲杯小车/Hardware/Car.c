#include "Device/Include/stm32f10x.h"   // Device header
#include "PWM.h"
#include "Motor.h"


void Car_Init(void)
{
   Motor_Init();
}


void Car_GoAhead(uint8_t carSpeed)
{
   Motor_SetSpeed1(carSpeed);
   Motor_SetSpeed2(carSpeed);
}

void Car_GoBack(uint8_t carSpeed)
{
   Motor_SetSpeed1(-carSpeed);
   Motor_SetSpeed2(-carSpeed);
}

void Car_TurnLeft(void)
{
Motor_LeftStop();
Motor_SetSpeed2(70);
}
void Car_TurnRight(void)
{
Motor_SetSpeed1(70);
Motor_RightStop();
}
void Car_Stop(void)
{
  Motor_LeftStop();
  Motor_RightStop();	
}