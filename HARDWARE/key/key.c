#include "stm32f10x.h" // Device header
#include "delay.h"
#include "key.h"

void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

#ifdef __USE_WK_UP

uint8_t KEY_Scan(int mode)
{
	static uint8_t key_up = 1; // key up flag
	if (mode)
		key_up = 1; // mode 1, need to release the key
	if (key_up)
	{
		if (KEY0 == 0 || KEY1 == 0)
		{
			delay_ms(5);
			key_up = 0;
			if (KEY0 == 0)
				return KEY0_PRES;
			else if (KEY1 == 0)
				return KEY1_PRES;
		}
	}
}

#elif !defined(__USE_WK_UP)

uint8_t KEY_Scan(int mode)
{
	static uint8_t key_up = 1; // key up flag
	if (mode)
		key_up = 1; // mode 1, need to release the key
	if (key_up)
	{
		if (KEY0 == 0 || KEY1 == 0 || WK_UP == 1)
		{
			delay_ms(5);
			key_up = 0;
			if (KEY0 == 0)
				return KEY0_PRES;
			else if (KEY1 == 0)
				return KEY1_PRES;
			else if (WK_UP == 1)
				return WKUP_PRES;
		}
	}
	else
	{
		if (KEY0 == 1 && KEY1 == 1 && WK_UP == 0)
			key_up = 1;
	}
	return NONE_PRES;
}

#endif
