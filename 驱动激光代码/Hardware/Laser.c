#include "stm32f10x.h"

void Laser_Init(void)
{
   
	
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
 
    GPIOA->CRL |= GPIO_CRL_MODE0;
    GPIOA->CRL &= ~GPIO_CRL_CNF0;
		GPIOA->ODR &= ~GPIO_ODR_ODR0;

}
 

void Laser_On(void)
{
    GPIOA->ODR |= GPIO_ODR_ODR0;
}
 

void Laser_Off(void)
{
    GPIOA->ODR &= ~GPIO_ODR_ODR0;
	 
}

void Laser_Toggle(void)
{
    
    if(GPIOA->ODR & GPIO_ODR_ODR0)
    {
        Laser_Off(); 
    }
    else
    {
        Laser_On(); 
    }
}