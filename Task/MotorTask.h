
#ifndef		_MOTOR_TASK_H_   
#define		_MOTOR_TASK_H_

#include "common.h"

#define		WATER_LEVER_MAX				30  //�趨���ˮλ
#define		WATER_LEVER_MIN			0  //�趨�޶�ˮλ

void MotorTask_Init(volatile u32 *ulSysClock);

void Motor_Task(void);


bool GetMotorCtrlFlag(void);

void SetMotorCtrlFlag(u8 dat);

void SwitchMotorCtrlFlag(void);

#endif //