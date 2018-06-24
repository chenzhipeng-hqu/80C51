
#include "KEYTask.h"
#include "KEY.h"
#include "EasyKey.h"
#include "MotorTask.h"
#include "UsartTask.h"

#define		KEY_TASK_TIME_DELAY		10

static volatile u32 *pulSysTicks;							 //用于记录系统时钟地址
static u32 ulOldTicks;							 //记录时间变量，与系统时间对比，查看延时时间是否到达

static u8	WaterLeverLimit = 10;

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void KEYTask_Init(volatile u32 *ulSysClock)
{
//	Key_Init();
 	pulSysTicks = ulSysClock;	
}

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void KEY_Task(void)
{
	s8 array[16] = {0};
	s16 Key_Val = 0;
	if ( (*pulSysTicks) - ulOldTicks >= KEY_TASK_TIME_DELAY )		  //记录时间变量与系统时间对比，查看延时时间是否到达
	{
		ulOldTicks = *pulSysTicks;					  //从新记录系统时间
//		Key_Val = Key_Scan();
//		sprintf(array,"%2d",(Key_Val));
//		LCD_Write_String(8,1,array);							
		
		//运行任务
		
		Read_Key();
						
		if((KEY_State[0] == Falling) | (KEY_State[0] == continue_L))
		{
			SwitchMotorCtrlFlag();
			P2 ^= (1<<6);
		}
		
		if((KEY_State[1] == Falling) | (KEY_State[1] == continue_L))
		{
			if(GetWaterLeverLimit() < WATER_LEVER_MAX)
			{
				SetWaterLeverLimit(GetWaterLeverLimit()+1);
			}
			
			P2 ^= (1<<6);
		}
		
		if((KEY_State[2] == Falling) | (KEY_State[2] == continue_L))
		{
			if(GetWaterLeverLimit() > WATER_LEVER_MIN)
			{
				SetWaterLeverLimit(GetWaterLeverLimit()-1);
			}
			
			P2 ^= (1<<6);
		}
		
		if((KEY_State[3] == Falling) | (KEY_State[3] == continue_L))
		{
			SetWaterLever(GetWaterLever()+1);
			P2 ^= (1<<6);
		}
		
		if((KEY_State[4] == Falling) | (KEY_State[4] == continue_L))
		{
			SetWaterLever(GetWaterLever()-1);		
			P2 ^= (1<<6);
		}
		
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
}

u8 SetWaterLeverLimit(u8 dat)
{
	WaterLeverLimit = dat;
}

u8 GetWaterLeverLimit(void)
{
	return WaterLeverLimit;
}


/**/