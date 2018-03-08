

#ifndef		_USART_TASK_H_   
#define		_USART_TASK_H_

#include "common.h"

extern u8 u8Cmd;

void UsartTask_Init(volatile u32 *ulSysClock);

void Usart_Task(void);

u8 GetWaterLever(void);

void SetWaterLever(u8 dat);

#endif //