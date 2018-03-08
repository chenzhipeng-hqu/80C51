
#include "KEYTask.h"
#include "KEY.h"
#include "EasyKey.h"
#include "MotorTask.h"
#include "UsartTask.h"

#define		KEY_TASK_TIME_DELAY		10

static volatile u32 *pulSysTicks;							 //用于记录系统时钟地址
static u32 ulOldTicks;							 //记录时间变量，与系统时间对比，查看延时时间是否到达


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
			P1 ^= (1<<6);
		}
		
		if((KEY_State[1] == Falling) | (KEY_State[1] == continue_L))
		{
			P1 ^= (1<<6);
		}
		
		if((KEY_State[2] == Falling) | (KEY_State[2] == continue_L))
		{
			P1 ^= (1<<6);
		}
		
		if((KEY_State[3] == Falling) | (KEY_State[3] == continue_L))
		{
			P1 ^= (1<<6);
		}
		
		
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
}


/**/