#include "stm32f10x.h"
#include "led.h"

void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// LED0
	GPIO_InitStructure.GPIO_Pin = LED0_GPIO_Pin;
	GPIO_Init(LED0_GPIO_Port, &GPIO_InitStructure);
	// LED1
	GPIO_InitStructure.GPIO_Pin = LED1_GPIO_Pin;
	GPIO_Init(LED1_GPIO_Port, &GPIO_InitStructure);
}

void LED0_ON()
{
	GPIO_ResetBits(LED0_GPIO_Port, LED0_GPIO_Pin);
}

void LED0_OFF()
{
	GPIO_SetBits(LED0_GPIO_Port, LED0_GPIO_Pin);
}

void LED1_ON()
{
	GPIO_ResetBits(LED1_GPIO_Port, LED1_GPIO_Pin);
}

void LED1_OFF()
{
	GPIO_SetBits(LED1_GPIO_Port, LED1_GPIO_Pin);
}
