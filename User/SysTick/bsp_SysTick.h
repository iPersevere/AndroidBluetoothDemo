#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"


#define TASK_ENABLE 0
#define NumOfTask 3

//void SysTick_Init(void);
void SysTick2_Init(void);
void Delay2_ms(__IO u32 nTime);
void SysTick_Delay_us(uint32_t us);
void mdelay(unsigned long nTime);
void Delay_us(__IO u32 nTime);         // 单位1us

int get_tick_count(unsigned long *count);
void TimeStamp_Increment(void);


#define Delay_ms(x) SysTick_Delay_us(1000*x)	 //单位ms

#endif /* __SYSTICK_H */
