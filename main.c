

/*	
	Code	程序代码存储区
	Data	直接寻址片内数据存储区（低128字节）
	Bdata	位寻址片内数据存储区（16字节）
	Idata	间接寻址片内数据存储区（256字节）
	Pdata	分页寻址外部数据存储区（256字节）
	Xdata	可寻址片外数据存储区(64KB）
*/

#include "common.h"
#include "Timer.h"
#include "PCA.h"

#include "LEDTask.h"
#include "LCD1602Task.h"

int main(void)  //reentrant //重入函数修饰符
{	
	volatile u32 *pulSysTicks;							 //用于记录系统时钟地址
	
	pulSysTicks = TM0_Init();
	
	PCA_Init();
	
	EA = 1;
	
	LEDTask_Init(pulSysTicks);
	LCD1602Task_Init(pulSysTicks);
	
	while(1)
	{
		LED_Task();
	
		LCD1602_Task();
	}
	
	return 0;
}