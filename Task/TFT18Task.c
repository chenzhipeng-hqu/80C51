
#include "TFT18Task.h"
#include "TFT18.h"


#define		TFT18_TASK_TIME_DELAY		100

static volatile u32 *pulSysTicks;							 //���ڼ�¼ϵͳʱ�ӵ�ַ
static u32 ulOldTicks;							 //��¼ʱ���������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�
u32	g_unMinusTicks = 0;
extern u8 g_ucNRF_Init_Flag;


/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void TFT18Task_Init(volatile u32 *ulSysClock)
{

	Lcd_Init();
	LCD_Clear(GREEN); //����	
	BACK_COLOR=WHITE;;POINT_COLOR=BLACK; 
	LCD_ShowCH(0*16,0*16,0);	//��
	LCD_ShowCH(1*16,0*16,1);	//��
	LCD_ShowCH(2*16,0*16,2);	//��
	LCD_ShowCH(3*16,0*16,4);	//ʪ
	LCD_ShowCH(4*16,0*16,5);	//��
	LCD_ShowCH(5*16,0*16,8);	//��
	LCD_ShowCH(6*16,0*16,9);	//��
//	P11 = 0;
	
 	pulSysTicks = ulSysClock;	
}

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void TFT18_Task(void)
{
	s8 array[16] = {0};
	static u16 unTemp;
//	unTemp = (*pulSysTicks) - ulOldTicks;
	if ( (*pulSysTicks) - ulOldTicks >= TFT18_TASK_TIME_DELAY )		  //��¼ʱ�������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�
	{
		ulOldTicks = *pulSysTicks;					  //���¼�¼ϵͳʱ��
		//��������
//		LCD_ShowString(4*8,8*16,"AB");
		
		sprintf(array,"%3ld %2d %3ld %1d",((*pulSysTicks)/1000),unTemp,g_unMinusTicks,(int)g_ucNRF_Init_Flag);
		LCD_ShowString(0*8,9*16,array);							//????
		
		unTemp = (*pulSysTicks) - ulOldTicks;
				
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
}
/**/