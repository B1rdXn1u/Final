#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"
#include "Serial.h"
#include "Laser.h"//添加激光头文件

uint8_t KeyNum;
int8_t Speed;

int main(void)
{
	OLED_Init();
	Motor_Init();
	Key_Init();
	Serial_Init();
  Laser_Init();//添加激光初始化
	OLED_ShowString(1, 1, "Speed:");

	while (1)//正数负数转动方向不一样
	{
		
		
		if(KeyNum==2)
		{
			Laser_Toggle();
		
		}//添加激光按键
		
	}

}


	
	
	
	
	
	
	