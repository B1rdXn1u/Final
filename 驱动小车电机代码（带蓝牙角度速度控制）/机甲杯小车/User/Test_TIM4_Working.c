#include "Device/Include/stm32f10x.h"   // Device header
void Test_TIM4_Only(void)
{
    // 1. 强制时钟
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    
    // 2. 配置PB8为复用推挽
    GPIOB->CRH &= ~(0xF << 0);
    GPIOB->CRH |= (0xB << 0);   // AF_PP, 50MHz
    
    // 3. 配置TIM4时基，50Hz
    TIM4->PSC = 71;
    TIM4->ARR = 19999;
    
    // 4. 配置TIM4_CH3为PWM模式
    TIM4->CCMR2 &= ~TIM_CCMR2_OC3M;
    TIM4->CCMR2 |= (0x6 << 4);  // PWM模式1
    TIM4->CCMR2 |= TIM_CCMR2_OC3PE;
    TIM4->CCER &= ~TIM_CCER_CC3P;
    TIM4->CCER |= TIM_CCER_CC3E;
    
    // 5. 设置占空比50%
    TIM4->CCR3 = 500;  // 0.5ms脉宽
    
    // 6. 启动TIM4
    TIM4->CR1 = TIM_CR1_ARPE | TIM_CR1_CEN;
    
    // 7. 验证关键寄存器
    volatile uint32_t check;
    check = TIM4->CR1;      // 应为0x81 (CEN=1, ARPE=1)
    check = TIM4->DIER;     // 应为0
    check = TIM4->SR;       // 清除状态
}
int main(void)
{
    Test_TIM4_Only();
    while(1);
}
