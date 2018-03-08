

#include "UsartTask.h"
#include "usart.h"
#include "EasyKey.h"

#define		USART_TASK_TIME_DELAY		15
#define		DT_HEAD						0xCC
#define 	DT_CMD_MASK         		0xF0
#define 	DT_LEN_MASK         		0x0F
#define 	DT_SIZE_MAX        			DATA_MAX

static volatile u32 *pulSysTicks;							 //用于记录系统时钟地址
static u32 ulOldTicks;							 //记录时间变量，与系统时间对比，查看延时时间是否到达

static u8 u8WaterLever = 0;
static u8 u8Cmd = 0;
static u8 u8Len = 0;
static u8 *pu8Data;

static u8 GetData(u8 *p, u8 len);
static u8 CheckData(u8 *p);
static u8 DecodeData(u8 *p);

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void UsartTask_Init(volatile u32 *ulSysClock)
{
	Usart_Init();
	SendString("Usart is OK!");
 	pulSysTicks = ulSysClock;	
}

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void Usart_Task(void)
{
	u8 i;
	if ( (*pulSysTicks) - ulOldTicks >= USART_TASK_TIME_DELAY )		  //记录时间变量与系统时间对比，查看延时时间是否到达
	{
		ulOldTicks = *pulSysTicks;					  //从新记录系统时间
		
		//运行任务
		if((KEY_State[0] == Falling) | (KEY_State[0] == continue_L))
		{
			SendString("KEY0 is press.\n");
		}
		if((KEY_State[1] == Falling) | (KEY_State[1] == continue_L))
		{
			SendString("KEY1 is press.\n");
		}
		
		for(i=0; i<DATA_MAX; i++)
		{
			//寻找幀头
			if(Receive_Buff[i] == DT_HEAD) 
			{			
				if(CheckData(&Receive_Buff[i]))    //计算校验位
				{
					P1 &= ~(1<<6);
					break;   //校验失败
				}
				
				u8Cmd = (Receive_Buff[i+1] & DT_CMD_MASK) >> 4;   //获取命令
				u8Len = (Receive_Buff[i+1] & DT_LEN_MASK) >> 0;		//获取payload长度
				
				pu8Data = malloc(u8Len);
				
				GetData(&Receive_Buff[i+2], u8Len);//获取payload数据;
				
				DecodeData(pu8Data);      //数据解码
				
				free(pu8Data);								
			}
			
			g_u8RxCnt = 0;
			memset(Receive_Buff,0,sizeof(Receive_Buff));
		}
						
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
}

u8 CheckData(u8 *p)
{
	u8 j,check;
	for(j=0; j<DT_SIZE_MAX-1; j++)
	{
		check += *(p+j);
	}
	
	check = 1-0xFF;   //串口软件发送测试用
	
	if((1-check) != *(p+j))  
	{
		return -1;  //校验失败
	}
	
	return 0;  //校验成功
}

u8 GetData(u8 *p, u8 len)
{
	u8 i;
	for(i=0; i<len; i++)
	{
		*(pu8Data+i) = *(p+i);
	}
	return 0;
}

u8 DecodeData(u8 *p)
{
	u8WaterLever = *p;
	return u8WaterLever;
}

u8 GetWaterLever(void)
{
	return u8WaterLever;
}

/**/
