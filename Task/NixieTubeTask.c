
#include "NixieTubeTask.h"
#include "NixieTube.h"
#include "Key.h"

#define		NIXIE_TUBE_TASK_TIME_DELAY		10

static volatile u32 *pulSysTicks;							 //���ڼ�¼ϵͳʱ�ӵ�ַ
static u32 ulOldTicks;							 //��¼ʱ���������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�

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
	if ( (*pulSysTicks) - ulOldTicks >= NIXIE_TUBE_TASK_TIME_DELAY )		  //��¼ʱ�������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�
	{
		ulOldTicks = *pulSysTicks;					  //���¼�¼ϵͳʱ��
		ntemp = Key_Scan();
		NixieTube_Disp(ntemp,ntemp);//��������
				
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
}
/**/