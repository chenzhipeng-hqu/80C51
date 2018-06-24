
#include "NRFTask.h"
#include "NRF24L01.h"


#define		NRF_TASK_TIME_DELAY		10

static volatile u32 *pulSysTicks;							 //���ڼ�¼ϵͳʱ�ӵ�ַ
static u32 ulOldTicks;							 //��¼ʱ���������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�

extern u32 g_ulSysTicks;      //ϵͳʱ��
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
	NRFSetRXMode();					//����Ϊ����ģʽ

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
	u8	Rx_IDn[RX_DATA_WITDH];//���ܵ�����
	u8	Tx_IDn[RX_DATA_WITDH] = {0x01,0x02,0x03,0x05};//���͵�����
	if ( (*pulSysTicks) - ulOldTicks >= NRF_TASK_TIME_DELAY )		  //��¼ʱ�������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�
	{
		ulOldTicks = *pulSysTicks;					  //���¼�¼ϵͳʱ��
		//��������
		g_ulOldTicks = g_ulSysTicks;
	
#ifndef		NRF_SEND
		NRF24L01Int();
		NRFSetRXMode();					//����Ϊ����ģʽ
		
		while(nMode = NRFRevDate(Rx_IDn) == ERROR)
		{
			if((*pulSysTicks) - ulOldTicks >= NRF_TASK_TIME_DELAY)
			{
				break ;       //����ȴ��źų�ʱ�������ȴ���
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
		NRFSetTxMode(Tx_IDn);//���Ͱ�����ֵ
		while(CheckACK());	//����Ƿ������	
		NRF24L01Int();					//��ʼ��24L01
		NRFSetRXMode();					//����Ϊ����ģʽ
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
		g_unMinusTicks = g_ulSysTicks - g_ulOldTicks;  //������������ʱ�䡣
				
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
}
/**/