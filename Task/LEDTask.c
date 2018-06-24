
#include "LED.h"
#include "LEDTask.h"

#define		LED_TASK_TIME_DELAY		500

static volatile u32 *pulSysTicks;							 //���ڼ�¼ϵͳʱ�ӵ�ַ
static u32 ulOldTicks;							 //��¼ʱ���������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�

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
	
	if ( (*pulSysTicks) - ulOldTicks >= LED_TASK_TIME_DELAY )		  //��¼ʱ�������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�
	{
		//���¼�¼ϵͳʱ��
		ulOldTicks = *pulSysTicks;				
		
		//��������	  
		LED0 = ~LED0;							  
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
}

/**/