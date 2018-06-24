

#include "MotorTask.h"
#include "KEYTask.h"
#include "UsartTask.h"

#define		MOTOR_TASK_TIME_DELAY		10

#define		MOTOR_CTRL(x)			Motor_Pin = x


sbit Motor_Pin = P1^4;

static volatile u32 *pulSysTicks;							 //���ڼ�¼ϵͳʱ�ӵ�ַ
static u32 ulOldTicks;							 //��¼ʱ���������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�

static u8 MotorCtrlFlag = 0;

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void MotorTask_Init(volatile u32 *ulSysClock)
{
	//LED_Init();
 	pulSysTicks = ulSysClock;	
	
	MOTOR_CTRL(OFF);
}

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void Motor_Task(void)
{
	
	if ( (*pulSysTicks) - ulOldTicks >= MOTOR_TASK_TIME_DELAY )		  //��¼ʱ�������ϵͳʱ��Աȣ��鿴��ʱʱ���Ƿ񵽴�
	{
		//���¼�¼ϵͳʱ��
		ulOldTicks = *pulSysTicks;					  
		
		//��������
		
		if( (GetWaterLever() < GetWaterLeverLimit()) && (GetWaterLever() < WATER_LEVER_MAX) ) //�����趨ˮλ�ҵ������ˮλ��򿪳�ˮ���� 
		{
			SetMotorCtrlFlag(ON);
		}
		else if( GetWaterLever() >= WATER_LEVER_MAX )
		{
			SetMotorCtrlFlag(OFF);
		}
		
		MOTOR_CTRL(GetMotorCtrlFlag());	
		
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
}

bool GetMotorCtrlFlag(void)
{
	return MotorCtrlFlag;
}

void SetMotorCtrlFlag(u8 dat)
{
	MotorCtrlFlag = dat;
}

void SwitchMotorCtrlFlag(void)
{
	MotorCtrlFlag = !MotorCtrlFlag;
}


/**/