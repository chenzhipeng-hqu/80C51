
#include "LED.h"
#include "LEDTask.h"

#define		LED_TASK_TIME_DELAY		500

static volatile u32 *pulSysTicks;							 //用于记录系统时钟地址
static u32 ulOldTicks;							 //记录时间变量，与系统时间对比，查看延时时间是否到达

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void LEDTask_Init(volatile u32 *ulSysClock)
{
	LED_Init();
 	pulSysTicks = ulSysClock;
	
	if( pulSysTicks == NULL )
	{
		return ;
	}	
}

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void LED_Task(void)
{
	
	if ( (*pulSysTicks) - ulOldTicks >= LED_TASK_TIME_DELAY )		  //记录时间变量与系统时间对比，查看延时时间是否到达
	{
		//从新记录系统时间
		ulOldTicks = *pulSysTicks;				
		
		//运行任务	  
		LED0 = ~LED0;							  
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
}

/**/