#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	 // 1. 禁用I2C1时钟（防止PB6/PB7被占用）
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, DISABLE);
    
    // 2. 使能定时器和GPIO时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    // 3. 时钟使能后短暂延迟，等待时钟稳定
    __ASM volatile ("nop");  // 汇编空指令延迟
    __ASM volatile ("nop");
    
    // 4. 配置GPIOA（PA2, PA3）
    GPIO_InitTypeDef GPIO_InitStructureA;
    GPIO_InitStructureA.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructureA.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructureA.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructureA);
    
    // 5. 配置GPIOB（PB6, PB7, PB8, PB9）
    GPIO_InitTypeDef GPIO_InitStructureB;
    GPIO_InitStructureB.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructureB.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructureB.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructureB);
	// 6. 配置TIM2时基（100Hz PWM）
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure2;
    TIM_TimeBaseInitStructure2.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure2.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure2.TIM_Period = 100 - 1;      // ARR
    TIM_TimeBaseInitStructure2.TIM_Prescaler = 720 - 1;    // PSC
    TIM_TimeBaseInitStructure2.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure2);
    
    // 7. 配置TIM4时基（50Hz PWM - 适合舵机）
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure4;
    TIM_TimeBaseInitStructure4.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure4.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure4.TIM_Period = 20000 - 1;    // ARR
    TIM_TimeBaseInitStructure4.TIM_Prescaler = 72 - 1;    // PSC
    TIM_TimeBaseInitStructure4.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure4);
    
    // 8. 配置TIM2的PWM通道（使用独立结构体）
    TIM_OCInitTypeDef TIM_OCInitStructure_TIM2;
    TIM_OCStructInit(&TIM_OCInitStructure_TIM2);
    TIM_OCInitStructure_TIM2.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure_TIM2.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure_TIM2.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure_TIM2.TIM_Pulse = 0;  // CCR初始为0
    
    TIM_OC3Init(TIM2, &TIM_OCInitStructure_TIM2);  // PA2
    TIM_OC4Init(TIM2, &TIM_OCInitStructure_TIM2);  // PA3
    
    // 9. 配置TIM4的PWM通道（使用独立结构体）
    TIM_OCInitTypeDef TIM_OCInitStructure_TIM4;
    TIM_OCStructInit(&TIM_OCInitStructure_TIM4);
    TIM_OCInitStructure_TIM4.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure_TIM4.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure_TIM4.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure_TIM4.TIM_Pulse = 0;  // CCR初始为0
	TIM_OC1Init(TIM4, &TIM_OCInitStructure_TIM4);  // PB6
    TIM_OC2Init(TIM4, &TIM_OCInitStructure_TIM4);  // PB7
    TIM_OC3Init(TIM4, &TIM_OCInitStructure_TIM4);  // PB8
    TIM_OC4Init(TIM4, &TIM_OCInitStructure_TIM4);  // PB9
    
    // 10. 预装载使能（关键！）
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
    
    // 11. 使能ARR预装载
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_ARRPreloadConfig(TIM4, ENABLE);
    
    // 12. 启动定时器
    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}



void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM2, Compare);
}//设置A2的PWM占空比

void PWM_SetCompare4(uint16_t Compare)
{
	TIM_SetCompare4(TIM2, Compare);
}//设置A3的PWM占空比
//电机控制

void PWM_SetCompare6(uint16_t Compare)
{
	TIM_SetCompare1(TIM4, Compare);
}//设置B6的PWM占空比(180度）
void PWM_SetCompare7(uint16_t Compare)
{
	TIM_SetCompare2(TIM4, Compare);
}//设置B7的PWM占空比（180度）
void PWM_SetCompare8(uint16_t Compare)
{
	TIM_SetCompare3(TIM4, Compare);
}//设置B8的PWM占空比（360度）
void PWM_SetCompare9(uint16_t Compare)
{
	TIM_SetCompare4(TIM4, Compare);
}//设置B9的PWM占空比（360度）

//舵机控制需将CCR值映射到500-2500（对应0.5-2.5ms）
