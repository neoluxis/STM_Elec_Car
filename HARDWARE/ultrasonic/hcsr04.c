#include "hcsr04.h"
#include "delay.h"

uint16_t N = 0;
float distance = 0;

//void CSB_SR04_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitSructure; //GPIO初始化
//	NVIC_InitTypeDef NVIC_InitSructure; //定时器初始化
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStrure;  //外部中断初始化
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能PB端口时钟
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//	
//	//PB6输出，PB7输入
//	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitSructure.GPIO_Pin = GPIO_Pin_6;
//	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitSructure);
//	
//	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_IPD;
//	GPIO_InitSructure.GPIO_Pin = GPIO_Pin_7;
//	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitSructure);
//	
//	//溢出时间tim=(arr+1)*(psc+1)/72000000
//	TIM_TimeBaseStrure.TIM_Period = 49999;
//	TIM_TimeBaseStrure.TIM_Prescaler = 72-1;
//	TIM_TimeBaseStrure.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseStrure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
//	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStrure);
//	
//	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);  //使能中断
//	NVIC_InitSructure.NVIC_IRQChannel = TIM4_IRQn;
//	NVIC_InitSructure.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级2级
//	NVIC_InitSructure.NVIC_IRQChannelSubPriority = 1;  //从优先级0级
//	NVIC_InitSructure.NVIC_IRQChannelCmd = ENABLE;  //IRQ通道使能
//	NVIC_Init(&NVIC_InitSructure);
//	
//	TIM_Cmd(TIM4,ENABLE);
//}

uint16_t N1 = 0;
float distance1 = 0;

void CSB_SR04_Init(void)
{
	GPIO_InitTypeDef GPIO_InitSructure; //GPIO初始化
	NVIC_InitTypeDef NVIC_InitSructure; //定时器初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStrure;  //外部中断初始化
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能PB端口时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	//PA0输出，PA1输入
	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitSructure);
	
	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitSructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitSructure);
	
	//溢出时间tim=(arr+1)*(psc+1)/72000000
	TIM_TimeBaseStrure.TIM_Period = 49999;
	TIM_TimeBaseStrure.TIM_Prescaler = 72-1;
	TIM_TimeBaseStrure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStrure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStrure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);  //使能中断
	NVIC_InitSructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitSructure.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级2级
	NVIC_InitSructure.NVIC_IRQChannelSubPriority = 1;  //从优先级0级
	NVIC_InitSructure.NVIC_IRQChannelCmd = ENABLE;  //IRQ通道使能
	NVIC_Init(&NVIC_InitSructure);
	
	TIM_Cmd(TIM4,ENABLE);
}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)
	{
		N += 1;
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //清除中断标志位
}

int count = 0;
//float Distance(void)
//{
//	GPIO_ResetBits(GPIOB,GPIO_Pin_6);  //预先拉低输出引脚
//	GPIO_SetBits(GPIOB,GPIO_Pin_6);
//	delay_us(20);
//	GPIO_ResetBits(GPIOB,GPIO_Pin_6);  //产生10us脉冲
//	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == 0);
//	TIM4->CNT=0;
//	
//	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == 1);
//	count = TIM4->CNT;
//	
//	distance = (float)count/58;
//	return distance;
//}

float Distance(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);  //预先拉低输出引脚
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	delay_us(20);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);  //产生10us脉冲
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0);
	TIM4->CNT=0;
	
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 1);
	count = TIM4->CNT;
	
	distance = (float)count/58;
	return distance;
}

//void CSB_SR04_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitSructure; //GPIO初始化
//	NVIC_InitTypeDef NVIC_InitSructure; //定时器初始化
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStrure;  //外部中断初始化
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能PB端口时钟
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//	
//	//PB6输出，PB7输入
//	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitSructure.GPIO_Pin = GPIO_Pin_6;
//	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitSructure);
//	
//	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_IPD;
//	GPIO_InitSructure.GPIO_Pin = GPIO_Pin_7;
//	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitSructure);
//	
//	//溢出时间tim=(arr+1)*(psc+1)/72000000
//	TIM_TimeBaseStrure.TIM_Period = 49999;
//	TIM_TimeBaseStrure.TIM_Prescaler = 72-1;
//	TIM_TimeBaseStrure.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseStrure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
//	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStrure);
//	
//	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);  //使能中断
//	NVIC_InitSructure.NVIC_IRQChannel = TIM4_IRQn;
//	NVIC_InitSructure.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级2级
//	NVIC_InitSructure.NVIC_IRQChannelSubPriority = 1;  //从优先级0级
//	NVIC_InitSructure.NVIC_IRQChannelCmd = ENABLE;  //IRQ通道使能
//	NVIC_Init(&NVIC_InitSructure);
//	
//	TIM_Cmd(TIM4,ENABLE);
//}

void MS1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitSructure; //GPIO初始化
	NVIC_InitTypeDef NVIC_InitSructure; //定时器初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStrure;  //外部中断初始化
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能PB端口时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//PA0输出，PA1输入
	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitSructure);
	
	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitSructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitSructure);
	
	//溢出时间tim=(arr+1)*(psc+1)/72000000
	TIM_TimeBaseStrure.TIM_Period = 49999;
	TIM_TimeBaseStrure.TIM_Prescaler = 72-1;
	TIM_TimeBaseStrure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStrure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStrure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);  //使能中断
	NVIC_InitSructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitSructure.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级2级
	NVIC_InitSructure.NVIC_IRQChannelSubPriority = 1;  //从优先级0级
	NVIC_InitSructure.NVIC_IRQChannelCmd = ENABLE;  //IRQ通道使能
	NVIC_Init(&NVIC_InitSructure);
	
	TIM_Cmd(TIM3,ENABLE);
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET)
	{
		N1 += 1;
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}

int count1 = 0;

float Distance1(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);  //预先拉低输出引脚
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	delay_us(20);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);  //产生10us脉冲
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) == 0);
	TIM3->CNT=0;
	
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) == 1);
	count1 = TIM3->CNT;
	
	distance1 = (float)count1/58;
	return distance1;
}


uint16_t N2 = 0;
float distance2 = 0;

void MS2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitSructure; //GPIO初始化
	NVIC_InitTypeDef NVIC_InitSructure; //定时器初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStrure;  //外部中断初始化
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能PB端口时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	
	//PA0输出，PA1输入
	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitSructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitSructure);
	
	GPIO_InitSructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitSructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitSructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitSructure);
	
	//溢出时间tim=(arr+1)*(psc+1)/72000000
	TIM_TimeBaseStrure.TIM_Period = 49999;
	TIM_TimeBaseStrure.TIM_Prescaler = 72-1;
	TIM_TimeBaseStrure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStrure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStrure);
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);  //使能中断
	NVIC_InitSructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitSructure.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级2级
	NVIC_InitSructure.NVIC_IRQChannelSubPriority = 1;  //从优先级0级
	NVIC_InitSructure.NVIC_IRQChannelCmd = ENABLE;  //IRQ通道使能
	NVIC_Init(&NVIC_InitSructure);
	
	TIM_Cmd(TIM5,ENABLE);
}

void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update) != RESET)
	{
		N2 += 1;
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志位
}

int count2 = 0;

float Distance2(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);  //预先拉低输出引脚
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	delay_us(20);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);  //产生10us脉冲
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) == 0);
	TIM5->CNT=0;
	
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) == 1);
	count2 = TIM5->CNT;
	
	distance2 = (float)count2/58;
	return distance2;
}




