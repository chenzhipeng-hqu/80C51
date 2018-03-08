
#ifndef		_MOTOR_TASK_H_   
#define		_MOTOR_TASK_H_

#include "common.h"

#define		WATER_LEVER_MAX				30  //设定最高水位
#define		WATER_LEVER_MIN			0  //设定限定水位

void MotorTask_Init(volatile u32 *ulSysClock);

void Motor_Task(void);


bool GetMotorCtrlFlag(void);

void SetMotorCtrlFlag(u8 dat);

void SwitchMotorCtrlFlag(void);

#endif //