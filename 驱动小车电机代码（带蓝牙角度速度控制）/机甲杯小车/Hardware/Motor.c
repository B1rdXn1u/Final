#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;//����A OUT
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	PWM_Init();
}

void Motor_LeftStop(void)
	{
	GPIO_ResetBits(GPIOB, GPIO_Pin_13);	
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);  
    PWM_SetCompare3(0);                    // 占空比0%
}
	void Motor_RightStop(void)
	{
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);	
    GPIO_ResetBits(GPIOB, GPIO_Pin_15);  
    PWM_SetCompare4(0);                    // 占空比0%
}
void Motor_SetSpeed1(uint8_t Speed)                
{
	if (Speed > 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
		PWM_SetCompare3(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
		PWM_SetCompare3(-Speed);
	}
}//左边轮子速度

void Motor_SetSpeed2(uint8_t Speed)
{
	if (Speed > 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
		PWM_SetCompare4(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
		PWM_SetCompare4(-Speed);
	}
}//右边轮子速度
