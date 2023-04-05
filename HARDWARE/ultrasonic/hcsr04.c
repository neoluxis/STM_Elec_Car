#include "stm32f10x.h"                  // Device header
#include "hcsr04.h"

void HCSR_Init(HCSR04_InitStruct* HCSR04){
	GPIO_InitTypeDef GPIO_InitSructure;
	NVIC_InitTypeDef NVIC_InitSructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStrure;  
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	//Trigger Pin & Echo Pin
	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSructure.GPIO_Pin = HCSR04->TriggerPin;
	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HCSR04->TriggerPort,&GPIO_InitSructure);
	
	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitSructure.GPIO_Pin = HCSR04->EchoPin;
	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(HCSR04->EchoPort,&GPIO_InitSructure);
	
	//辰?3?那㊣??tim=(arr+1)*(psc+1)/72000000
	TIM_TimeBaseStrure.TIM_Period = 49999;
	TIM_TimeBaseStrure.TIM_Prescaler = 72-1;
	TIM_TimeBaseStrure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStrure.TIM_CounterMode = TIM_CounterMode_Up; //?辰谷???那y
	TIM_TimeBaseInit(HCSR04->HCSR_Timer,&TIM_TimeBaseStrure);
	
	TIM_ITConfig(HCSR04->HCSR_Timer,TIM_IT_Update,ENABLE);  //那1?邦?D??
	NVIC_InitSructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitSructure.NVIC_IRQChannelPreemptionPriority = 1;  //?角??車??豕??2??
	NVIC_InitSructure.NVIC_IRQChannelSubPriority = 1;  //∩車車??豕??0??
	NVIC_InitSructure.NVIC_IRQChannelCmd = ENABLE;  //IRQ赤“米角那1?邦
	NVIC_Init(&NVIC_InitSructure);
	
	TIM_Cmd(HCSR04->HCSR_Timer,ENABLE);
}
