#ifndef __HCSR04_H
#define __HCSR04_H
#include "stm32f10x.h"                  // Device header

/**
* 
*/
void HCSR_Init(GPIO_TypeDef* TriggerPort,uint16_t TriggerPin,GPIO_TypeDef* EchoPort,uint16_t EchoPin);


#endif
