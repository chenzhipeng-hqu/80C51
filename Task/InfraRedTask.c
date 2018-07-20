
#include "InfraRed.h"
#include "InfraRedTask.h"

//test
sbit LED7 = P1^7;


#define		INFRARED_TASK_TIME_DELAY		500

static volatile u32 *pulSysTicks;							 //���ڼ�¼ϵͳʱ�ӵ�ַ
static u32 ulOldTicks;							 //��¼ʱ���������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�

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
	
	if ( (*pulSysTicks) - ulOldTicks >= INFRARED_TASK_TIME_DELAY )		  //��¼ʱ�������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�
	{
		//���¼�¼ϵͳʱ��
		ulOldTicks = *pulSysTicks;				
		
		//��������	  
		InfraRed_RX_Calculate();	
		LED7 = !LED7;
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
}

/**/