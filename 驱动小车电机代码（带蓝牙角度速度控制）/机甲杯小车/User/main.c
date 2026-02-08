#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Motor.h"
#include "Key.h"
#include "Serial.h"
#include "Servo.h"
#include "Car.h"
#include "PWM.h"
#include "String.h"
#include <stdio.h>
#include <stdlib.h>
#include "Laser.h"
int8_t SpeedNum;
uint8_t FinalSpeed;
uint8_t FinalAngle1;
uint8_t FinalAngle2;
int main(void)
{
	Serial_Init();
	Car_Init();
	PWM_Init();
	FinalSpeed = 5;
	FinalAngle1 = 90;
	FinalAngle2 = 90;
		while (1)
	{
		if (Serial_RxFlag == 1)
		{
			
			char * Tag = strtok(Serial_RxPacket,",");
			if (strcmp(Tag, "key")==0)
			{
			char * Name = strtok(NULL,",");
			char * Action = strtok(NULL,",");
			if (strcmp(Name, "1")==0 && strcmp(Action, "down")==0)
			{
			SpeedNum =  1;
			}//前进
			
			
			if (strcmp(Name, "1")==0 && strcmp(Action, "up")==0)
			{
			SpeedNum =  0;
			}//停止
			if (strcmp(Name, "2")==0 && strcmp(Action, "down")==0)
			{
			SpeedNum =  -1;
			}//后退
			if (strcmp(Name, "2")==0 && strcmp(Action, "up")==0)
			{
			SpeedNum = 0;
			}//停止
			if (strcmp(Name, "3")==0 && strcmp(Action, "down")==0)
			{
			SpeedNum = 2;
			}//左转
			if (strcmp(Name, "3")==0 && strcmp(Action, "up")==0)
			{
			SpeedNum = 0;
			}//停止
			if (strcmp(Name, "4")==0 && strcmp(Action, "down")==0)
			{
			SpeedNum = -2;
			}//右转
			if (strcmp(Name, "4")==0 && strcmp(Action, "up")==0)
			{
			SpeedNum = 0;
			} //停止
			if (strcmp(Name, "5")==0 && strcmp(Action, "down")==0)
			{
			SpeedNum =  1;
			}//前进
			}//接受方向按键信息
			
			
			
			else if ( strcmp(Tag, "slider") == 0)
			{
			char *Name = strtok(NULL,",");
			char *Value = strtok(NULL,",");
			
			if(strcmp(Name,"1") == 0)
			{
			FinalSpeed = atoi(Value); 
				if (SpeedNum != 0) {
                    // 根据当前方向重新应用速度
                    if (SpeedNum == 1) Car_GoAhead(FinalSpeed);
                    else if (SpeedNum == -1) Car_GoBack(FinalSpeed);
                    // 转向时保持原逻辑，或根据需要调整
                }
			}
			if(strcmp(Name,"2") == 0)
			{
			FinalAngle1 = atoi(Value);
			}
			if(strcmp(Name,"3") == 0)
			{
			FinalAngle2 = atoi(Value);
			}
			}
			
			}
		Serial_RxFlag = 0;
			if (SpeedNum == 0)
			{
			 Car_Stop();
			}
			if (SpeedNum == 1)
			{
			 Car_GoAhead(FinalSpeed);
			}
			if(SpeedNum == -1)
			{
			Car_GoBack(FinalSpeed);
			}
			if(SpeedNum == 2)
			{
			Car_TurnLeft();
			}
			if(SpeedNum == -2)
			{
			Car_TurnRight();
			}//方向
			 switch(SpeedNum)
    {
        case 0:   // 停止
            Car_Stop(); 
            break;
        case 1:   // 前进（使用最新FinalSpeed）
            Car_GoAhead(FinalSpeed); 
            break;
        case -1:  // 后退（使用最新FinalSpeed）
            Car_GoBack(FinalSpeed); 
            break;
        case 2:   // 左转（保持原逻辑，或改为可调速）
            Car_TurnLeft(); 
            break;
        case -2:  // 右转
            Car_TurnRight(); 
            break;
    }
		Servo_SetAngle6(FinalAngle1);//B6舵机角度
        Servo_SetAngle7(FinalAngle2);//B7舵机角度
			
			
}


}



