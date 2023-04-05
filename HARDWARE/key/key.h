#ifndef __KEY_H
#define __KEY_H
#include "stm32f10x.h"                  // Device header

#define NONE_PRES 0
#define KEY0_PRES 1
#define KEY1_PRES 2
#define WKUP_PRES 3

#define KEY0 PCin(1)   //PC1
#define KEY1 PCin(13)	//PC13 
#define WK_UP PAin(0)	//PA0  WK_UP

void Key_Init(void);
uint8_t Key_GetNum(void);

#endif
