

#include "MotorTask.h"
#include "KEYTask.h"
#include "UsartTask.h"

#define		MOTOR_TASK_TIME_DELAY		10

#define		MOTOR_CTRL(x)			Motor_Pin = x


sbit Motor_Pin = P1^4;

static volatile u32 *pulSysTicks;							 //用于记录系统时钟地址
static u32 ulOldTicks;							 //记录时间变量，与系统时间对比，查看延时时间是否到达

static u8 MotorCtrlFlag = 0;

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void MotorTask_Init(volatile u32 *ulSysClock)
{
	//LED_Init();
 	pulSysTicks = ulSysClock;	
	
	MOTOR_CTRL(OFF);
}

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void Motor_Task(void)
{
	
	if ( (*pulSysTicks) - ulOldTicks >= MOTOR_TASK_TIME_DELAY )		  //记录时间变量与系统时间对比，查看延时时间是否到达
	{
		//从新记录系统时间
		ulOldTicks = *pulSysTicks;					  
		
		//运行任务
		
		if( (GetWaterLever() < GetWaterLeverLimit()) && (GetWaterLever() < WATER_LEVER_MAX) ) //低于设定水位且低于最高水位则打开抽水开关 
		{
			SetMotorCtrlFlag(ON);
		}
		else if( GetWaterLever() >= WATER_LEVER_MAX )
		{
			SetMotorCtrlFlag(OFF);
		}
		
		MOTOR_CTRL(GetMotorCtrlFlag());	
		
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
}

bool GetMotorCtrlFlag(void)
{
	return MotorCtrlFlag;
}

void SetMotorCtrlFlag(u8 dat)
{
	MotorCtrlFlag = dat;
}

void SwitchMotorCtrlFlag(void)
{
	MotorCtrlFlag = !MotorCtrlFlag;
}


/**/