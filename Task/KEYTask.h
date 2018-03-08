

#ifndef		_KEY_TASK_H_   
#define		_KEY_TASK_H_

#include "common.h"


void KEYTask_Init(volatile u32 *ulSysClock);

void KEY_Task(void);

u8 SetWaterLeverLimit(u8 dat);

u8 GetWaterLeverLimit(void);

#endif //