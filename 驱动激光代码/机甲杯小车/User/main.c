#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"
#include "Serial.h"

uint8_t KeyNum;
int8_t Speed;

int main(void)
{
	OLED_Init();
	Motor_Init();
	Key_Init();
	Serial_Init();
	OLED_ShowString(1, 1, "Speed:");

	while (1)//正数负数转动方向不一样
	{
		
	
		Motor_SetSpeed1(70);
		Motor_SetSpeed2(70);
		
	}

}


	
	
	
	
	
	
	