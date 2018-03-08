

#include "UsartTask.h"
#include "usart.h"
#include "EasyKey.h"

#define		USART_TASK_TIME_DELAY		15
#define		DT_HEAD						0xCC
#define 	DT_CMD_MASK         		0xF0
#define 	DT_LEN_MASK         		0x0F
#define 	DT_SIZE_MAX        			DATA_MAX

#define DT_USER_CMD_1    1
#define DT_USER_CMD_2    2
#define DT_USER_CMD_3    3
#define DT_USER_CMD_4    4
#define DT_USER_CMD_5    5
#define DT_USER_CMD_6    6
#define DT_USER_CMD_7    7
#define DT_USER_CMD_8    8
#define DT_USER_CMD_9    9
#define DT_USER_CMD_10   10
#define DT_USER_CMD_11   11
#define DT_USER_CMD_12   12
#define DT_USER_CMD_13   13
#define DT_USER_CMD_14   14
#define DT_USER_CMD_15   15

static volatile u32 *pulSysTicks;							 //用于记录系统时钟地址
static u32 ulOldTicks;							 //记录时间变量，与系统时间对比，查看延时时间是否到达

static u8 u8WaterLever = 0;
u8 u8Cmd = 0;
static u8 u8Len = 0;
static u8 *pu8Data = NULL;

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
	u8 SendBuf_temp = {0};
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
		for(i=0; i<DATA_MAX; i++)
		{
			//寻找幀头
			if(Receive_Buff[i] == DT_HEAD) 
			{
				u8Cmd = (Receive_Buff[i+1] & DT_CMD_MASK) >> 4;   //获取命令
				u8Len = (Receive_Buff[i+1] & DT_LEN_MASK) >> 0;		//获取payload长度
				
				if(CheckData(&Receive_Buff[i]))    //计算校验位
				{
					P1 &= ~(1<<6);
					break;   //校验失败
				}			
				
				if(u8Cmd == DT_USER_CMD_1)
				{
					//	pu8Data = (u8 *)malloc(sizeof(unsigned char)*DATA_MAX);
				
				//	u8WaterLever = Receive_Buff[i+2];  //获取payload数据;
					
					DecodeData(&Receive_Buff[i+3]);   //数据解码
					
					P2 ^= (1<<5);
					
				//	free(pu8Data);					
				}	
				
				P2 ^= (1<<3);
				
				g_u8RxCnt = 0;
				memset(Receive_Buff,0,sizeof(Receive_Buff));
			}
		}	
						
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
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
	
	if(u8WaterLever>30)
	{
		u8WaterLever = 30;
	}

	u8WaterLever = 30-u8WaterLever;
		
	return u8WaterLever;
}

u8 CheckData(u8 *p)
{
	u8 j,check;
	for(j=0; j<(u8Len+2); j++)
	{
		check += *(p+j);
	}
	
//	check = 1-0xFF;   //串口软件发送测试用
	
	if((1-check) != *(p+j))  
	{
		return -1;  //校验失败
	}
	
	return 0;  //校验成功
}

void SetWaterLever(u8 dat)
{
	u8WaterLever = dat;
}

u8 GetWaterLever(void)
{
	return u8WaterLever;
}

/**/
