
#include "NixieTubeTask.h"
#include "NixieTube.h"
#include "Key.h"

#define		NIXIE_TUBE_TASK_TIME_DELAY		10

static volatile u32 *pulSysTicks;							 //用于记录系统时钟地址
static u32 ulOldTicks;							 //记录时间变量，与系统时间对比，查看延时时间是否到达

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void NixieTubeTask_Init(volatile u32 *ulSysClock)
{	
 	pulSysTicks = ulSysClock;		
	NixieTube_Init();
}

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void NixieTube_Task(void)
{
	static s8 ntemp;
	if ( (*pulSysTicks) - ulOldTicks >= NIXIE_TUBE_TASK_TIME_DELAY )		  //记录时间变量与系统时间对比，查看延时时间是否到达
	{
		ulOldTicks = *pulSysTicks;					  //从新记录系统时间
		ntemp = Key_Scan();
		NixieTube_Disp(ntemp,ntemp);//运行任务
				
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
}
/**/