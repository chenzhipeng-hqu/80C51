

/*	
	Code	�������洢��
	Data	ֱ��ѰַƬ�����ݴ洢������128�ֽڣ�
	Bdata	λѰַƬ�����ݴ洢����16�ֽڣ�
	Idata	���ѰַƬ�����ݴ洢����256�ֽڣ�
	Pdata	��ҳѰַ�ⲿ���ݴ洢����256�ֽڣ�
	Xdata	��ѰַƬ�����ݴ洢��(64KB��
*/

#include "common.h"
#include "Timer.h"
#include "PCA.h"
#include "task.h"
#include "led.h"

#include "LEDTask.h"
#include "LCD1602Task.h"

TaskTypeDef xdata Task_Array[] = {
	{SUSPEND, 	0, 		0,		NULL,				Idle_Task},
	{SUSPEND, 	500, 	500, 	LED_Init,		LED_Task},
	{SUSPEND, 	50, 	50, 	NULL,		LCD1602_Task},
};

int main(void)  //reentrant //���뺯�����η�
{	
	volatile u32 *pulSysTicks;							 //���ڼ�¼ϵͳʱ�ӵ�ַ
	
	pulSysTicks = TM0_Init();
	
	PCA_Init();
	
	EA = 1;
	
	TaskInitial(sizeof(Task_Array)/sizeof(Task_Array[0]));
	LEDTask_Init(pulSysTicks);
	LCD1602Task_Init(pulSysTicks);
	
	while(1)
	{
//		LED_Task();
//	
//		LCD1602_Task();
		
		TaskScheduler();
	}
	
	return 0;
}
