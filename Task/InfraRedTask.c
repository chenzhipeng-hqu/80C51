
#include "InfraRed.h"
#include "InfraRedTask.h"

//test
sbit LED7 = P1^7;


#define		INFRARED_TASK_TIME_DELAY		500

static volatile u32 *pulSysTicks;							 //用于记录系统时钟地址
static u32 ulOldTicks;							 //记录时间变量，与系统时间对比，查看延时时间是否到达

/**
  * @brief  InfraRedTask_Init
  * @param  
  * @retval 
  */
void InfraRedTask_Init(volatile u32 *ulSysClock)
{
	if( pulSysTicks == NULL )
	{
		return ;
	}	
		
	PCA_Init();
	InfraRed_RX_Init();
 	pulSysTicks = ulSysClock;
	
}

/**
  * @brief  InfraRed_Task
  * @param  
  * @retval 
  */
void InfraRed_Task(void)
{
	
	if ( (*pulSysTicks) - ulOldTicks >= INFRARED_TASK_TIME_DELAY )		  //记录时间变量与系统时间对比，查看延时时间是否到达
	{
		//从新记录系统时间
		ulOldTicks = *pulSysTicks;				
		
		//运行任务	  
		InfraRed_RX_Calculate();	
		LED7 = !LED7;
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
}

/**/