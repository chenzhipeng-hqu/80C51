
#include "NRFTask.h"
#include "NRF24L01.h"


#define		NRF_TASK_TIME_DELAY		10

static volatile u32 *pulSysTicks;							 //用于记录系统时钟地址
static u32 ulOldTicks;							 //记录时间变量，与系统时间对比，查看延时时间是否到达

extern u32 g_ulSysTicks;      //系统时间
static u32 g_ulOldTicks;
extern u32	g_unMinusTicks;

u8 g_ucNRF_Init_Flag = ERROR;

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void NRFTask_Init(volatile u32 *ulSysClock)
{
	NRF24L01Int();
	NRFSetRXMode();					//设置为接收模式

	if( Nrf24l01_Check() == SUCCESS )
	{
		g_ucNRF_Init_Flag = SUCCESS;
		P11 = 0;
	}
	else if( Nrf24l01_Check() == ERROR)
	{
		g_ucNRF_Init_Flag = ERROR;
		P11 = 1;
	}

 	pulSysTicks = ulSysClock;	
}

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void NRF_Task(void)
{
	s8 array[16] = {0};
	static s16 nMode = 0;
	u8	Rx_IDn[RX_DATA_WITDH];//接受的数据
	u8	Tx_IDn[RX_DATA_WITDH] = {0x01,0x02,0x03,0x05};//发送的数据
	if ( (*pulSysTicks) - ulOldTicks >= NRF_TASK_TIME_DELAY )		  //记录时间变量与系统时间对比，查看延时时间是否到达
	{
		ulOldTicks = *pulSysTicks;					  //从新记录系统时间
		//运行任务
		g_ulOldTicks = g_ulSysTicks;
	
#ifndef		NRF_SEND
		NRF24L01Int();
		NRFSetRXMode();					//设置为接收模式
		
		while(nMode = NRFRevDate(Rx_IDn) == ERROR)
		{
			if((*pulSysTicks) - ulOldTicks >= NRF_TASK_TIME_DELAY)
			{
				break ;       //如果等待信号超时则跳出等待。
			}
		}
		
//		nMode = SUCCESS;
		
		if(Rx_IDn[3] == 0x04)
		{
			P17 = 0;
		}
		else if( (Rx_IDn[3] == 0x05) )
		{
			P16 = 0;
		}
		else
		{
			P16 = 1;
			P17 = 1;
		}
		
		Rx_IDn[3] = 0;
				
#else	

		NRF24L01Int();
		NRFSetTxMode(Tx_IDn);//发送按键数值
		while(CheckACK());	//检测是否发送完毕	
		NRF24L01Int();					//初始化24L01
		NRFSetRXMode();					//设置为接收模式
		P17 = 0;
		
#endif
		
		switch(nMode)
		{
			case 0:
				
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				break;
		}
		g_unMinusTicks = g_ulSysTicks - g_ulOldTicks;  //测试任务运行时间。
				
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
}
/**/