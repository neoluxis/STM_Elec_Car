#include "hcsr04.h"
#include "delay.h"

void HCSR04_Init(HCSR04_Structure *hcsr04)
{
	GPIO_InitTypeDef GPIO_InitSructure;			// GPIO初始化
	NVIC_InitTypeDef NVIC_InitSructure;			// 定时器初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStrure; // 外部中断初始化

	hcsr04->RCC_APBxPeriphClockCmd_Trigger(hcsr04->RCC_APBxPeriph_GPIOx_Trigger, ENABLE); // enable trigger gpio clock
	hcsr04->RCC_APBxPeriphClockCmd_Echo(hcsr04->RCC_APBxPeriph_GPIOx_Echo, ENABLE);		  // enable echo gpio clock
	hcsr04->RCC_APBxPeriphClockCmd_TIMx(hcsr04->RCC_APBxPeriph_TIMx, ENABLE);			  // enable timer clock

	// trigger output
	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSructure.GPIO_Pin = hcsr04->TriggerPin;
	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(hcsr04->TriggerPort, &GPIO_InitSructure);

	// echo input
	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitSructure.GPIO_Pin = hcsr04->EchoPin;
	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(hcsr04->EchoPort, &GPIO_InitSructure);

	// timer, overflow time t = (arr + 1) * (psc + 1) / 72000000
	TIM_TimeBaseStrure.TIM_Period = 49999;					 // 50000 * 1 / 72000000 = 0.000694444s = 694.444us
	TIM_TimeBaseStrure.TIM_Prescaler = 72 - 1;				 // 72 * 1 / 72000000 = 0.000001s = 1us
	TIM_TimeBaseStrure.TIM_ClockDivision = TIM_CKD_DIV1;	 // 时钟分频因子
	TIM_TimeBaseStrure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
	TIM_TimeBaseInit(hcsr04->TIMx, &TIM_TimeBaseStrure);	 // 初始化定时器

	TIM_ITConfig(hcsr04->TIMx, TIM_IT_Update, ENABLE); // 使能中断
	NVIC_InitSructure.NVIC_IRQChannel = hcsr04->NVIC_IRQ_Channel;
	NVIC_InitSructure.NVIC_IRQChannelPreemptionPriority = 1; // 抢占优先级2级
	NVIC_InitSructure.NVIC_IRQChannelSubPriority = 1;		 // 从优先级0级
	NVIC_InitSructure.NVIC_IRQChannelCmd = ENABLE;			 // IRQ通道使能
	NVIC_Init(&NVIC_InitSructure);

	TIM_Cmd(hcsr04->TIMx, ENABLE);
}

double HCSR04_GetDistance(HCSR04_Structure *hcsr04)
{
	GPIO_ResetBits(hcsr04->TriggerPort, hcsr04->TriggerPin); // trigger low
	GPIO_SetBits(hcsr04->TriggerPort, hcsr04->TriggerPin);	 // trigger high
	delay_us(10);											 // 10us pulse
	GPIO_ResetBits(hcsr04->TriggerPort, hcsr04->TriggerPin); // trigger low
	while (GPIO_ReadInputDataBit(hcsr04->EchoPort, hcsr04->EchoPin) == 0)
		;
	TIM_SetCounter(hcsr04->TIMx, 0); // reset counter
	while (GPIO_ReadInputDataBit(hcsr04->EchoPort, hcsr04->EchoPin) == 1)
		;
	hcsr04->count = TIM_GetCounter(hcsr04->TIMx);
	if ((float)hcsr04->count / 58 < 100)
	{
		hcsr04->distance = (float)hcsr04->count / 58; // 58 = 1 / 0.00001715
	}
	return hcsr04->distance;
}

uint16_t N = 0;
float distance = 0;
