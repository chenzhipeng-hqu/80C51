

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

static volatile u32 *pulSysTicks;							 //���ڼ�¼ϵͳʱ�ӵ�ַ
static u32 ulOldTicks;							 //��¼ʱ���������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�

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
	if ( (*pulSysTicks) - ulOldTicks >= USART_TASK_TIME_DELAY )		  //��¼ʱ�������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�
	{
		ulOldTicks = *pulSysTicks;					  //���¼�¼ϵͳʱ��
		
		//��������
		for(i=0; i<DATA_MAX; i++)
		{
			//Ѱ�Ҏ�ͷ
			if(Receive_Buff[i] == DT_HEAD) 
			{
				u8Cmd = (Receive_Buff[i+1] & DT_CMD_MASK) >> 4;   //��ȡ����
				u8Len = (Receive_Buff[i+1] & DT_LEN_MASK) >> 0;		//��ȡpayload����
				
				if(CheckData(&Receive_Buff[i]))    //����У��λ
				{
					P1 &= ~(1<<6);
					break;   //У��ʧ��
				}			
				
				if(u8Cmd == DT_USER_CMD_1)
				{
					//	pu8Data = (u8 *)malloc(sizeof(unsigned char)*DATA_MAX);
				
				//	u8WaterLever = Receive_Buff[i+2];  //��ȡpayload����;
					
					DecodeData(&Receive_Buff[i+3]);   //���ݽ���
					
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
	
//	check = 1-0xFF;   //����������Ͳ�����
	
	if((1-check) != *(p+j))  
	{
		return -1;  //У��ʧ��
	}
	
	return 0;  //У��ɹ�
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
