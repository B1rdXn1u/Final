#include "Device/Include/stm32f10x.h"   // Device header
#include "PWM.h"

void Servo_Init(void)
{
   PWM_Init();
}


void Servo_SetAngle6(float Angle)
{
    PWM_SetCompare6(Angle / 180 * 2000 + 500) ; 
}

void Servo_SetAngle7(float Angle)
{
    PWM_SetCompare7(Angle / 180 * 2000 + 500) ; 
}

void Servo_SetAngle8(uint16_t Angle)
{
    uint16_t ccr = (uint16_t)((float)Angle / 360.0f * 2000.0f + 500.5f);
    PWM_SetCompare8(ccr);
}

void Servo_SetAngle9(uint16_t Angle)
{
    uint16_t ccr = (uint16_t)((float)Angle / 360.0f * 2000.0f + 500.5f);
    PWM_SetCompare9(ccr);
}
