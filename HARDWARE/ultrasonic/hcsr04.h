#ifndef __HCSR04_H
#define __HCSR04_H

#include "stm32f10x.h"                  // Device header
#include "delay.h"

typedef struct {
	// GPIO Echo and Trigger
	GPIO_TypeDef* TriggerPort;
	uint16_t TriggerPin;
	GPIO_TypeDef* EchoPort;
	uint16_t EchoPin;
	// Timer
	uint32_t RCC_APB1Periph_TIM;
	TIM_TypeDef* HCSR_Timer;
	// Interupt
	uint8_t NVIC_IRQChannel;
	// Need no configuration
	int distance;
	int count;
	int N;
} HCSR04_InitStruct;

/**
* 
*/
void HCSR_Init(HCSR04_InitStruct* HCSR04);


#endif
