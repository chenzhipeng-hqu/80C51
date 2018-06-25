
#include "LCD1602Task.h"
#include "LCD1602.h"
#include "EasyKey.h"
#include "PCA.h"

#define		LCD1602_TASK_TIME_DELAY		20

static volatile u32 *pulSysTicks;							 //���ڼ�¼ϵͳʱ�ӵ�ַ
static u32 ulOldTicks;							 //��¼ʱ���������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void LCD1602Task_Init(volatile u32 *ulSysClock)
{
	LCD_Init();
 	pulSysTicks = ulSysClock;	
	LCD_Write_String(0,0," welcome to tri..");	
}

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void LCD1602_Task(void)
{
	s8 array[16] = {0};
	if ( (*pulSysTicks) - ulOldTicks >= LCD1602_TASK_TIME_DELAY )		  //��¼ʱ�������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�
	{
		ulOldTicks = *pulSysTicks;					  //���¼�¼ϵͳʱ��
		
		//��������	
		
		sprintf(array,"%4ld", (u32)((*pulSysTicks)/1000));
		LCD_Write_String(12,0,array);

		if(B_Capture1 == 1)
		{
			B_Capture1 = 0;
			sprintf(array,"%5d", (u16)(CCAP1_tmp));
			LCD_Write_String(0,1,array);
			CCAP1_tmp = 0;
		}
				
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
}
/**/