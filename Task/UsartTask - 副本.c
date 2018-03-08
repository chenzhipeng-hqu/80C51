

#include "UsartTask.h"
#include "usart.h"
#include "EasyKey.h"

#define		USART_TASK_TIME_DELAY		15
#define		DT_HEAD						0xCC
#define 	DT_CMD_MASK         		0xF0
#define 	DT_LEN_MASK         		0x0F
#define 	DT_SIZE_MAX        			DATA_MAX

static volatile u32 *pulSysTicks;							 //���ڼ�¼ϵͳʱ�ӵ�ַ
static u32 ulOldTicks;							 //��¼ʱ���������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�

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
	if ( (*pulSysTicks) - ulOldTicks >= USART_TASK_TIME_DELAY )		  //��¼ʱ�������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�
	{
		ulOldTicks = *pulSysTicks;					  //���¼�¼ϵͳʱ��
		
		//��������
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
			//Ѱ�Ҏ�ͷ
			if(Receive_Buff[i] == DT_HEAD) 
			{			
				if(CheckData(&Receive_Buff[i]))    //����У��λ
				{
					P1 &= ~(1<<6);
					break;   //У��ʧ��
				}
				
				u8Cmd = (Receive_Buff[i+1] & DT_CMD_MASK) >> 4;   //��ȡ����
				u8Len = (Receive_Buff[i+1] & DT_LEN_MASK) >> 0;		//��ȡpayload����
				
				pu8Data = malloc(u8Len);
				
				GetData(&Receive_Buff[i+2], u8Len);//��ȡpayload����;
				
				DecodeData(pu8Data);      //���ݽ���
				
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
	
	check = 1-0xFF;   //����������Ͳ�����
	
	if((1-check) != *(p+j))  
	{
		return -1;  //У��ʧ��
	}
	
	return 0;  //У��ɹ�
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
