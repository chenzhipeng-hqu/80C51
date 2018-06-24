
#ifndef		_NRF24L01_TASK_H_   
#define		_NRF24L01_TASK_H_

#include "common.h"


void NRFTask_Init(volatile u32 *ulSysClock);

void NRF_Task(void);




#endif //