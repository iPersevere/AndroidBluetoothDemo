/**
  ******************************************************************************
  * @file    bsp_SysTick.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   SysTick 系统滴答时钟10us中断函数库,中断时间可自由配置，
  *          常用的有 1us 10us 1ms 中断。     
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
//SysTick_Config主要用来配置中端向量，重置STK_VAL寄存器，配置SysTick时钟为AHB 
#include "./systick/bsp_SysTick.h"
 
static __IO uint32_t TimingDelay=0;
__IO uint32_t g_ul_ms_ticks=0;
 


/**
  * @brief  启动系统滴答定时器 SysTick2
  * @param  无
  * @retval 无
  */
void SysTick2_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if (SysTick_Config(SystemCoreClock/1000000))	
	{ 
		/* Capture error */ 
		while (1);
	}
		// 关闭滴答定时器  
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief  启动系统滴答定时器 SysTick
  * @param  无
  * @retval 无
  */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if (SysTick_Config(SystemCoreClock/1000))	
	{ 
		/* Capture error */ 
		while (1);
	}
		// 关闭滴答定时器  
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}


void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
		TimingDelay--;
}

void mdelay(unsigned long nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);
}


int get_tick_count(unsigned long *count)
{
        count[0] = g_ul_ms_ticks;
	return 0;
}



void TimeStamp_Increment(void)
{
	g_ul_ms_ticks++;
}


/**
  * @brief   us延时程序,1us为一个单位
  * @param  
  *		@arg nTime: Delay_us( 1 ) 则实现的延时为 1 * 1us = 1us
  * @retval  无
  */
void Delay_us(__IO u32 nTime)
{ 
	//SysTick_Init();
	TimingDelay = nTime;	

	// 使能滴答定时器  
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
	//SysTick2_Init();
}

void SysTick_Delay_us( __IO uint32_t us)
{
	uint32_t i;
	printf("Start finished\n");
	SysTick_Config(SystemCoreClock/1000000);
	printf("SysTick_Config finished\n");
	for(i=0;i<us;i++)
	{
		// 当计数器的值减小到0的时候，CRTL寄存器的位16会置1	
		while( !((SysTick->CTRL)&(1<<16)) );//countflag是否为1
	}
	printf("for xunhuan finished\n");
	// 关闭SysTick定时器
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}





/*********************************************END OF FILE**********************/
