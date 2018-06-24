
#include "TFT18Task.h"
#include "TFT18.h"


#define		TFT18_TASK_TIME_DELAY		100

static volatile u32 *pulSysTicks;							 //用于记录系统时钟地址
static u32 ulOldTicks;							 //记录时间变量，与系统时间对比，查看延时时间是否到达
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
	LCD_Clear(GREEN); //清屏	
	BACK_COLOR=WHITE;;POINT_COLOR=BLACK; 
	LCD_ShowCH(0*16,0*16,0);	//粮
	LCD_ShowCH(1*16,0*16,1);	//仓
	LCD_ShowCH(2*16,0*16,2);	//温
	LCD_ShowCH(3*16,0*16,4);	//湿
	LCD_ShowCH(4*16,0*16,5);	//度
	LCD_ShowCH(5*16,0*16,8);	//管
	LCD_ShowCH(6*16,0*16,9);	//理
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
	if ( (*pulSysTicks) - ulOldTicks >= TFT18_TASK_TIME_DELAY )		  //记录时间变量与系统时间对比，查看延时时间是否到达
	{
		ulOldTicks = *pulSysTicks;					  //从新记录系统时间
		//运行任务
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