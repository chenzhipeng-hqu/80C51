
#include "KEYTask.h"
#include "KEY.h"
#include "EasyKey.h"
#include "MotorTask.h"
#include "UsartTask.h"

#define		KEY_TASK_TIME_DELAY		10

static volatile u32 *pulSysTicks;							 //���ڼ�¼ϵͳʱ�ӵ�ַ
static u32 ulOldTicks;							 //��¼ʱ���������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�


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
	if ( (*pulSysTicks) - ulOldTicks >= KEY_TASK_TIME_DELAY )		  //��¼ʱ�������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�
	{
		ulOldTicks = *pulSysTicks;					  //���¼�¼ϵͳʱ��
//		Key_Val = Key_Scan();
//		sprintf(array,"%2d",(Key_Val));
//		LCD_Write_String(8,1,array);							
		
		//��������
		
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