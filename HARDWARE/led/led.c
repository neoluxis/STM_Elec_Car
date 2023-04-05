#include "stm32f10x.h"                  // Device header
#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
}

void LED0_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
}

void LED0_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
}

void LED0_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8) == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
	}
	else
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	}
}

void LED1_ON(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_4);
}

void LED1_OFF(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
}

void LED1_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_4) == 0) 
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_4);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_4);
	}
}

