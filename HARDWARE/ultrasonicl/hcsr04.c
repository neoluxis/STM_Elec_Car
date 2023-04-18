#include "stm32f10x.h"                  // Device header
#include "hcsr04.h"

void HCSR_Init(HCSR04_InitStruct* HCSR04){
	GPIO_InitTypeDef GPIO_InitSructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStrure;  
	NVIC_InitTypeDef NVIC_InitSructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(HCSR04->RCC_APB1Periph_TIM, ENABLE);
	
	//Trigger Pin & Echo Pin
	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSructure.GPIO_Pin = HCSR04->TriggerPin;
	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HCSR04->TriggerPort,&GPIO_InitSructure);
	
	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitSructure.GPIO_Pin = HCSR04->EchoPin;
	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HCSR04->EchoPort,&GPIO_InitSructure);
	
	//ò?3?ê±??tim=(arr+1)*(psc+1)/72000000
	TIM_TimeBaseStrure.TIM_Period = 49999;
	TIM_TimeBaseStrure.TIM_Prescaler = 72-1;
	TIM_TimeBaseStrure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStrure.TIM_CounterMode = TIM_CounterMode_Up; //?òé???êy
	TIM_TimeBaseInit(HCSR04->HCSR_Timer,&TIM_TimeBaseStrure);
	
	TIM_ITConfig(HCSR04->HCSR_Timer,TIM_IT_Update,ENABLE);  //ê1?ü?D??
	
	NVIC_InitSructure.NVIC_IRQChannel=HCSR04->NVIC_IRQChannel;
	NVIC_InitSructure.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级2级
	NVIC_InitSructure.NVIC_IRQChannelSubPriority = 1;  //从优先级0级
	NVIC_InitSructure.NVIC_IRQChannelCmd = ENABLE;  //IRQ通道使能

	NVIC_Init(&NVIC_InitSructure);
	
	TIM_Cmd(HCSR04->HCSR_Timer,ENABLE);
}

int ReadDistance(HCSR04_InitStruct* HCSR04){
	GPIO_ResetBits(HCSR04->TriggerPort,HCSR04->TriggerPin);  //预先拉低输出引脚
	GPIO_SetBits(HCSR04->TriggerPort,HCSR04->TriggerPin);
	delay_us(10);
	GPIO_ResetBits(HCSR04->TriggerPort,HCSR04->TriggerPin);  //产生10us脉冲
	while(GPIO_ReadInputDataBit(HCSR04->EchoPort,HCSR04->EchoPin) == 0);
	(HCSR04->HCSR_Timer)->CNT=0;
	
	while(GPIO_ReadInputDataBit(HCSR04->EchoPort,HCSR04->EchoPin) == 1);
	HCSR04->count = (HCSR04->HCSR_Timer)->CNT;
	
	HCSR04->distance = (float)(HCSR04->count)/58;
	return HCSR04->distance;
}


